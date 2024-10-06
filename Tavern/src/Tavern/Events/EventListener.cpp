#include "Tavern/Events/EventListener.h"

namespace Tavern
{
	int EventListener::s_Counter = 0;

	EventListener::EventListener(CallbackFunction&& callbackFunction)
		: m_CallbackFunction(callbackFunction)
	{
		s_Counter++;
		m_ID = s_Counter;
	}

	void EventListener::Call(const std::shared_ptr<Event>& event)
	{
		m_CallbackFunction(event);
	}

	const int EventListener::GetID() const
	{
		return m_ID;
	}
}

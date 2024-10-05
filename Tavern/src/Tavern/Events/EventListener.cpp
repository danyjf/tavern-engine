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

	const CallbackFunction& EventListener::GetCallbackFunction() const
	{
		return m_CallbackFunction;
	}

	const int EventListener::GetID() const
	{
		return m_ID;
	}
}

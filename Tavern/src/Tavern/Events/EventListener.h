#pragma once

#include <functional>
#include <memory>

#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventListenerInterface.h"

namespace Tavern
{
	template <typename T>
	using CallbackFunction = std::function<void(const std::shared_ptr<T>&)>;

	// Class used to register event listeners to the EventManager.
	// Remember to always manually remove the event listener from the
	// EventManager in the destructor of your class.
	template <typename T>
	class EventListener : public EventListenerInterface
	{
	public:
		EventListener(CallbackFunction<T>&& callbackFunction)
			: m_CallbackFunction(callbackFunction)
		{
			s_Counter++;
			m_ID = s_Counter;
		}

		void Call(const std::shared_ptr<Event>& event)
		{
			m_CallbackFunction(std::dynamic_pointer_cast<T>(event));
		}

		const int GetID() const
		{
			return m_ID;
		}

	private:
		CallbackFunction<T> m_CallbackFunction;
		int m_ID;

		inline static int s_Counter = 0;
	};
}

#pragma once

#include <functional>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	using CallbackFunction = std::function<void(const std::shared_ptr<Event>&)>;

	// Class used to register event listeners to the EventManager.
	// Remember to always manually remove the event listener from the
	// EventManager in the destructor of your class.
	class TAVERN_API EventListener
	{
	public:
		EventListener(CallbackFunction&& eventDelegate);

		const CallbackFunction& GetCallbackFunction() const;
		const int GetID() const;

	private:
		CallbackFunction m_CallbackFunction;
		int m_ID;

		static int s_Counter;
	};
}

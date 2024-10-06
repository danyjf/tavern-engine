#pragma once

#include <functional>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	// TODO: Change events so that the type of the event in the callback is in a template
	using CallbackFunction = std::function<void(const std::shared_ptr<Event>&)>;

	// Class used to register event listeners to the EventManager.
	// Remember to always manually remove the event listener from the
	// EventManager in the destructor of your class.
	class TAVERN_API EventListener
	{
	public:
		EventListener(CallbackFunction&& eventDelegate);

		void Call(const std::shared_ptr<Event>&);
		const int GetID() const;

	private:
		CallbackFunction m_CallbackFunction;
		int m_ID;

		static int s_Counter;
	};
}

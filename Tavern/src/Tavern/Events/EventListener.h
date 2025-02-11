#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class EventManager;
	class Event;

	class TAVERN_API EventListener
	{
	public:
		EventListener(EventManager& eventManager, const std::string& eventName, std::function<void(const std::shared_ptr<Event>)> callback);
		~EventListener();
		EventListener(const EventListener& other) = delete;
		EventListener& operator=(const EventListener& other) = delete;

		void Disable();
		void Enable();

		const std::string& GetEventName() const;

	private:
		EventManager& m_EventManager;
		std::string m_EventName;
		std::function<void(const std::shared_ptr<Event>)> m_Callback;
		unsigned long m_CallbackID;
		bool m_IsEnabled = true;
	};
}

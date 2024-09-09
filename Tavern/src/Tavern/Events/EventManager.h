#pragma once

#include "Event.h"

namespace Tavern
{
	class EventManager
	{
	public:
		// Singletons can not be clonable
		EventManager(EventManager& copy) = delete;
		// Singletons can not be assignable
		void operator=(const EventManager& copy) = delete;

		static EventManager& Get();

		using EventListenerDelegate = std::function<void(const std::shared_ptr<Event>&)>;

		// Register a delegate function to be called when the event type is triggered.
		// Returns true if successful.
		void AddListener(const EventType& type, EventListenerDelegate&& eventDelegate);

		// Add an event to the end of the queue
		// Returns true if successful.
		void QueueEvent(const std::shared_ptr<Event>& event);

		// Process all events from the queue
		// Returns true if successful.
		void ProcessEvents();

	private:
		// Contructor of singleton should be private
		EventManager() {};

		std::queue<std::shared_ptr<Event> > m_Events;
		std::unordered_map<EventType, std::vector<EventListenerDelegate> > m_EventListeners;
	};
}

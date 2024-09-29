#pragma once

#include <queue>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	class TAVERN_API EventManager
	{
	public:
		EventManager() {};
		~EventManager() {};
		EventManager(EventManager& copy) = delete;
		void operator=(const EventManager& copy) = delete;

		void Init();
		void Shutdown();

		using EventListenerDelegate = std::function<void(const std::shared_ptr<Event>&)>;

		// Register a delegate function to be called when the event type is triggered.
		// Returns true if successful.
		void AddListener(const EventType& type, EventListenerDelegate&& eventDelegate);

		// Add an event to the end of the queue
		// Returns true if successful.
		void QueueEvent(const std::shared_ptr<Event>& event);

		// Process all events from the queue
		// Returns true if successful.
		void DispatchEvents();

	private:
		std::queue<std::shared_ptr<Event>> m_Events;
		std::unordered_map<EventType, std::vector<EventListenerDelegate>> m_EventListeners;
	};

	extern TAVERN_API EventManager gEventManager;
}

#pragma once

#include <queue>
#include <unordered_map>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	class EventListener;

	class TAVERN_API EventManager
	{
	public:
		EventManager();
		~EventManager();
		EventManager(EventManager& copy) = delete;
		void operator=(const EventManager& copy) = delete;

		// Register a delegate function to be called when the event type is triggered.
		void AddListener(const EventType& type, EventListener& eventListener);
		void AddListener(const EventType& type, EventListener&& eventListener) = delete;

		void RemoveListener(const EventType& type, EventListener& eventListener);

		// TODO: Add a way to trigger an event ignoring the queue

		// Add an event to the end of the queue
		void QueueEvent(const std::shared_ptr<Event>& event);

		// Process all events from the queue
		void DispatchEvents();

	private:
		std::queue<std::shared_ptr<Event>> m_Events;
		std::unordered_map<EventType, std::vector<EventListener*>> m_EventListeners;
	};
}

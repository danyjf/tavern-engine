#pragma once

#include <queue>
#include <unordered_map>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventListenerInterface.h"

namespace Tavern
{
	class EventListenerInterface;

	class TAVERN_API EventManager
	{
	public:
		EventManager();
		~EventManager();
		EventManager(EventManager& copy) = delete;
		EventManager& operator=(const EventManager& copy) = delete;

		// Register a delegate function to be called when the event type is triggered.
		void AddListener(const EventType& type, EventListenerInterface& eventListener);
		void AddListener(const EventType& type, EventListenerInterface&& eventListener) = delete;

		void RemoveListener(const EventType& type, EventListenerInterface& eventListener);

		// Immediately trigger an event ignoring the queue
		void TriggerEvent(const std::shared_ptr<Event>& event);

		// Add an event to the end of the queue
		void QueueEvent(const std::shared_ptr<Event>& event);

	private:
		std::queue<std::shared_ptr<Event>> m_Events;
		std::unordered_map<EventType, std::vector<EventListenerInterface*>> m_EventListeners;

		// Process all events from the queue
		void DispatchEvents();

		friend class Engine;
	};
}

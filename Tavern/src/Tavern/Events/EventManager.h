#pragma once

#include <queue>
#include <unordered_map>
#include <string>
#include <functional>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	class TAVERN_API EventManager
	{
	public:
		EventManager();
		~EventManager();
		EventManager(EventManager& copy) = delete;
		EventManager& operator=(const EventManager& copy) = delete;

		// Immediately trigger an event ignoring the queue
		void TriggerEvent(const std::shared_ptr<Event> event);

		// Add an event to the end of the queue
		void QueueEvent(const std::shared_ptr<Event> event);

	private:
		inline static unsigned long s_CallbackCounter = 0;
		std::queue<std::shared_ptr<Event>> m_Events;

		using CallbackFunction = std::function<void(const std::shared_ptr<Event>)>;
		std::unordered_map<std::string, std::vector<std::pair<unsigned long, CallbackFunction>>> m_EventListeners;

		// Register a delegate function to be called when the event is triggered.
		unsigned long AddListener(const std::string& eventName, CallbackFunction callback);

		void RemoveListener(const std::string& eventName, unsigned long callbackID);

		// Process all events from the queue
		void DispatchEvents();

		friend class Engine;
		friend class EventListener;
	};
}

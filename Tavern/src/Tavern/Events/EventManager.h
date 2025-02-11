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

		// Register a delegate function to be called when the event is triggered.
		using CallbackFunction = std::function<void(const std::shared_ptr<Event>)>;
		unsigned long AddListener(const std::string& eventName, CallbackFunction callback);

		void RemoveListener(const std::string& eventName, unsigned long callbackID);

		// Immediately trigger an event ignoring the queue
		void TriggerEvent(const std::shared_ptr<Event> event);

		// Add an event to the end of the queue
		void QueueEvent(const std::shared_ptr<Event> event);

	private:
		inline static unsigned long s_CallbackCounter = 0;
		std::queue<std::shared_ptr<Event>> m_Events;
		std::unordered_map<std::string, std::vector<std::pair<unsigned long, CallbackFunction>>> m_EventListeners;

		// Process all events from the queue
		void DispatchEvents();

		friend class Engine;
	};
}

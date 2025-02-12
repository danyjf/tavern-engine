#pragma once

#include <queue>
#include <unordered_map>
#include <string>
#include <functional>
#include <typeindex>

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
		template <typename T>
		void TriggerEvent(const std::shared_ptr<T> event)
		{
			static_assert(std::is_base_of<Event, T>, "T must be derived from Event");

			// Ignore events that have no observer yet
			auto it = m_EventListeners.find(typeid(T));
			if (it == m_EventListeners.end())
			{
				return;
			}

			for (auto& [id, callback] : it->second)
			{
				callback(event);
			}
		}

		// Add an event to the end of the queue
		template <typename T>
		void QueueEvent(const std::shared_ptr<T> event)
		{
			static_assert(std::is_base_of<Event, T>, "T must be derived from Event");

			m_Events.emplace(typeid(T), event);
		}

	private:
		inline static unsigned long s_CallbackCounter = 0;
		std::queue<std::pair<std::type_index, std::shared_ptr<Event>>> m_Events;
		std::unordered_map<std::type_index, std::vector<std::pair<unsigned long, std::function<void(const std::shared_ptr<Event>)>>>> m_EventListeners;

		// Register a delegate function to be called when the event is triggered.
		template <typename T>
		unsigned long AddListener(std::function<void(const std::shared_ptr<T>)> callback)
		{
			static_assert(std::is_base_of<Event, T>, "T must be derived from Event");
			unsigned long callbackID = s_CallbackCounter++;
			m_EventListeners[typeid(T)].emplace_back(callbackID, [callback](const std::shared_ptr<Event> event) {
				callback(std::static_pointer_cast<T>(event));
			});
			return callbackID;
		}

		template <typename T>
		void RemoveListener(unsigned long callbackID)
		{
			static_assert(std::is_base_of<Event, T>, "T must be derived from Event");

			// Ignore if the event doesn't exist
			auto it = m_EventListeners.find(typeid(T));
			if (it == m_EventListeners.end())
				return;

			auto& listeners = it->second;
			std::erase_if(listeners, 
				[callbackID](const auto& listener) {
					return listener.first == callbackID;
				});
		}

		// Process all events from the queue
		void DispatchEvents();

		friend class Engine;

		template <typename T>
		friend class EventListener;
	};
}

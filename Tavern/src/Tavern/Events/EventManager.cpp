#include <vector>

#include "Tavern/Events/EventManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	EventManager::EventManager()
	{
		TAVERN_ENGINE_INFO("EventManager initialized");
	}

	EventManager::~EventManager()
	{
		TAVERN_ENGINE_INFO("EventManager destroyed");
	}

	unsigned long EventManager::AddListener(const std::string& eventName, CallbackFunction callback)
	{
		unsigned long callbackID = s_CallbackCounter++;
		m_EventListeners[eventName].emplace_back(callbackID, callback);
		return callbackID;
	}

	void EventManager::RemoveListener(const std::string& eventName, unsigned long callbackID)
	{
		// Ignore if the event doesn't exist
		if (m_EventListeners.find(eventName) == m_EventListeners.end())
			return;

		auto& listeners = m_EventListeners[eventName];
		std::erase_if(listeners, 
			[callbackID](std::pair<unsigned long, CallbackFunction> listener) {
				return listener.first == callbackID;
			});
	}

	void EventManager::TriggerEvent(const std::shared_ptr<Event> event)
	{
		// Ignore events that have no observer yet
		if (m_EventListeners.find(event->GetName()) == m_EventListeners.end())
			return;

		for (auto& [id, callback] : m_EventListeners[event->GetName()])
		{
			callback(event);
		}
	}

	void EventManager::QueueEvent(const std::shared_ptr<Event> event)
	{
		// Ignore events that have no observer yet
		if (m_EventListeners.find(event->GetName()) == m_EventListeners.end())
		{
			return;
		}

		m_Events.push(event);
	}

	void EventManager::DispatchEvents()
	{
		while (!m_Events.empty())
		{
			std::shared_ptr<Event> event = m_Events.front();

			if (m_EventListeners.find(event->GetName()) != m_EventListeners.end())
			{
				for (auto& [id, callback] : m_EventListeners[event->GetName()])
				{
					callback(event);
				}
			}

			m_Events.pop();
		}
	}
}

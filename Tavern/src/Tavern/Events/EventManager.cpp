#include <vector>

#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/EventListener.h"
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

	void EventManager::DispatchEvents()
	{
		while (!m_Events.empty())
		{
			auto& [eventType, event] = m_Events.front();

			auto it = m_EventListeners.find(eventType);
			if (it != m_EventListeners.end())
			{
				for (auto& [id, callback] : it->second)
				{
					callback(event);
				}
			}

			m_Events.pop();
		}
	}
}

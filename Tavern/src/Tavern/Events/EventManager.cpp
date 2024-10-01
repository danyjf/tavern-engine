#include "Tavern/Events/EventManager.h"

namespace Tavern
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::AddListener(const EventType& type, EventListenerDelegate&& eventDelegate)
	{
		m_EventListeners[type].push_back(eventDelegate);
	}

	void EventManager::QueueEvent(const std::shared_ptr<Event>& event)
	{
		// Ignore events that have no observer yet
		if (m_EventListeners.find(event->GetEventType()) == m_EventListeners.end())
			return;

		m_Events.push(event);
	}

	void EventManager::DispatchEvents()
	{
		while (!m_Events.empty())
		{
			std::shared_ptr<Event>& event = m_Events.front();

			if (m_EventListeners.find(event->GetEventType()) == m_EventListeners.end())
				continue;

			for (EventListenerDelegate& listener : m_EventListeners[event->GetEventType()])
			{
				listener(event);
			}

			m_Events.pop();
		}
	}
}

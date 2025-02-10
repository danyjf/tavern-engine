#include "Tavern/Events/EventManager.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Events/EventListenerInterface.h"
#include <vector>

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

	void EventManager::AddListener(const std::string& eventName, EventListenerInterface& eventListener)
	{
		m_EventListeners[eventName].push_back(&eventListener);
	}

	void EventManager::RemoveListener(const std::string& eventName, EventListenerInterface& eventListener)
	{
		// Ignore if the event doesn't exist
		if (m_EventListeners.find(eventName) == m_EventListeners.end())
			return;

		std::vector<EventListenerInterface*>& listeners = m_EventListeners[eventName];

		std::erase_if(listeners, [&eventListener](EventListenerInterface* storedListener) {
			return storedListener->GetID() == eventListener.GetID();
		});
	}

	void EventManager::TriggerEvent(const std::shared_ptr<Event>& event)
	{
		// Ignore events that have no observer yet
		if (m_EventListeners.find(event->GetName()) == m_EventListeners.end())
			return;

		for (EventListenerInterface* eventListener : m_EventListeners[event->GetName()])
		{
			eventListener->Call(event);
		}
	}

	void EventManager::QueueEvent(const std::shared_ptr<Event>& event)
	{
		// Ignore events that have no observer yet
		if (m_EventListeners.find(event->GetName()) == m_EventListeners.end())
			return;

		m_Events.push(event);
	}

	void EventManager::DispatchEvents()
	{
		while (!m_Events.empty())
		{
			std::shared_ptr<Event>& event = m_Events.front();

			if (m_EventListeners.find(event->GetName()) == m_EventListeners.end())
			{
				m_Events.pop();
				continue;
			}

			for (EventListenerInterface* eventListener : m_EventListeners[event->GetName()])
			{
				eventListener->Call(event);
			}

			m_Events.pop();
		}
	}
}

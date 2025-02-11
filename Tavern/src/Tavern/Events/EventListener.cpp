#include "Tavern/Events/EventListener.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/Event.h"

namespace Tavern
{
	EventListener::EventListener(EventManager& eventManager, const std::string& eventName, std::function<void(const std::shared_ptr<Event>)> callback)
		: m_EventManager(eventManager),
		  m_EventName(eventName),
		  m_Callback(callback),
		  m_IsEnabled(true)
	{
		m_CallbackID = m_EventManager.AddListener(m_EventName, m_Callback);
	}

	EventListener::~EventListener()
	{
		m_EventManager.RemoveListener(m_EventName, m_CallbackID);
	}

	void EventListener::Disable()
	{
		if (m_IsEnabled)
		{
			m_EventManager.RemoveListener(m_EventName, m_CallbackID);
			m_IsEnabled = false;
		}
	}

	void EventListener::Enable()
	{
		if (!m_IsEnabled)
		{
			m_CallbackID = m_EventManager.AddListener(m_EventName, m_Callback);
			m_IsEnabled = true;
		}
	}

	const std::string& EventListener::GetEventName() const
	{
		return m_EventName;
	}
}

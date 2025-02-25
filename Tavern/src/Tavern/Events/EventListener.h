#pragma once

#include <typeindex>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventManager.h"

namespace Tavern
{
	template <typename T>
	class EventListener
	{
	public:
		EventListener(EventManager& eventManager, std::function<void(const std::shared_ptr<T>)> callback)
			: m_EventManager(eventManager),
			  m_Callback(callback)
		{
			static_assert(std::is_base_of_v<Event, T>, "T must be derived from Event");
			m_CallbackID = m_EventManager.AddListener<T>(m_Callback);
		}

		~EventListener()
		{
			m_EventManager.RemoveListener<T>(m_CallbackID);
		}

		EventListener(const EventListener& other) = delete;
		EventListener& operator=(const EventListener& other) = delete;

		void Disable()
		{
			if (m_IsEnabled)
			{
				m_EventManager.RemoveListener<T>(m_CallbackID);
				m_IsEnabled = false;
			}
		}

		void Enable()
		{
			if (!m_IsEnabled)
			{
				m_CallbackID = m_EventManager.AddListener<T>(m_Callback);
				m_IsEnabled = true;
			}
		}

	private:
		EventManager& m_EventManager;
		std::function<void(const std::shared_ptr<T>)> m_Callback;
		unsigned long m_CallbackID;
		bool m_IsEnabled = true;
	};
}

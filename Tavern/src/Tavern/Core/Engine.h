#pragma once

#include <memory>
#include <vector>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Event;
	class Entity;
	class EventManager;
	class RenderManager;
	class InputManager;

	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		template <typename EntityClass>
		Entity* CreateEntity()
		{
			m_Entities.push_back(new EntityClass(this));
			return m_Entities.back();
		}

		EventManager* GetEventManager();
		RenderManager* GetRenderManager();
		InputManager* GetInputManager();

		void OnWindowCloseEvent(const std::shared_ptr<Event>& event);

	private:
		std::unique_ptr<EventManager> m_EventManager;
		std::unique_ptr<RenderManager> m_RenderManager;
		std::unique_ptr<InputManager> m_InputManager;

		bool m_IsRunning = true;

		std::vector<Entity*> m_Entities;
	};
}

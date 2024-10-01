#pragma once

#include <memory>
#include <vector>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"

namespace Tavern
{
	class Event;
	class Entity;

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

		EventManager& GetEventManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();

		void OnWindowCloseEvent(const std::shared_ptr<Event>& event);

	private:
		EventManager m_EventManager;
		RenderManager m_RenderManager;
		InputManager m_InputManager;

		bool m_IsRunning = true;

		std::vector<Entity*> m_Entities;
	};
}

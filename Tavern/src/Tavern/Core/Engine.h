#pragma once

#include <memory>
#include <vector>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	class Event;

	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		template <typename EntityClass>
		Entity* CreateEntity()
		{
			m_Entities.push_back(std::make_unique<EntityClass>(this));
			return m_Entities.back().get();
		}

		EventManager& GetEventManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();

		void OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event);

	private:
		EventManager m_EventManager = EventManager();
		RenderManager m_RenderManager = RenderManager(m_EventManager);
		InputManager m_InputManager = InputManager(m_RenderManager);
		EventListener<WindowCloseEvent> m_WindowCloseListener;

		bool m_IsRunning = true;

		std::vector<std::unique_ptr<Entity>> m_Entities = {};
	};
}

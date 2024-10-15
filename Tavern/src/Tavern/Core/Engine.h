#pragma once

#include <memory>
#include <vector>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Entity.h"
#include "Tavern/Resources/ResourceManager.h"

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
		EntityClass* CreateEntity()
		{
			m_Entities.push_back(std::make_unique<EntityClass>(this));
			return static_cast<EntityClass*>(m_Entities.back().get());
		}

		EventManager& GetEventManager();
		ResourceManager& GetResourceManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();

		void OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event);

	private:
		EventManager m_EventManager = EventManager();
		ResourceManager m_ResourceManager = ResourceManager();
		RenderManager m_RenderManager = RenderManager(m_EventManager);
		InputManager m_InputManager = InputManager(m_RenderManager);
		EventListener<WindowCloseEvent> m_WindowCloseListener;

		bool m_IsRunning = true;

		std::vector<std::unique_ptr<Entity>> m_Entities = {};
	};
}

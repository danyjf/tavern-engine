#pragma once

#include <memory>

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
			std::unique_ptr<EntityClass> entity = std::make_unique<EntityClass>(this);
			EntityClass* pEntity = entity.get();
			m_Entities.emplace(entity->GetID(), std::move(entity));
			return pEntity;
		}
		void DestroyEntity(Entity* entity);

		EventManager& GetEventManager();
		ResourceManager& GetResourceManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();

		void OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event);

	private:
		EventManager m_EventManager = EventManager();
		ResourceManager m_ResourceManager = ResourceManager();
		RenderManager m_RenderManager = RenderManager(m_EventManager, m_ResourceManager);
		InputManager m_InputManager = InputManager(m_RenderManager);
		EventListener<WindowCloseEvent> m_WindowCloseListener;

		bool m_IsRunning = true;

		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
	};
}

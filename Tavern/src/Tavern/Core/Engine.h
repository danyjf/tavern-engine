#pragma once

#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Scene/Scene.h"

namespace Tavern
{
	class Event;

	// TODO: Add lighting to the rendering
	// TODO: Add UI
	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		EventManager& GetEventManager();
		ResourceManager& GetResourceManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();
		Scene& GetScene();

		void OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event);

	private:
		EventManager m_EventManager = EventManager();
		ResourceManager m_ResourceManager = ResourceManager();
		RenderManager m_RenderManager = RenderManager(m_EventManager, m_ResourceManager);
		InputManager m_InputManager = InputManager(m_RenderManager);
		Scene m_Scene;

		EventListener<WindowCloseEvent> m_WindowCloseListener;

		bool m_IsRunning = true;
	};
}

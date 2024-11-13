#pragma once

#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Time.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Scene/Scene.h"

namespace Tavern
{
	class Event;

	// TODO: Create layers so that I can have a game layer and an editor layer
	// TODO: Create editor interface
	// TODO: Add PBR
	// TODO: Add multiple lights
	// TODO: Add different types of lights
	// TODO: Add audio
	// TODO: Add UI
	// TODO: Add physics
	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		void Update();
		void Render();

		bool IsRunning();

		EventManager& GetEventManager();
		ResourceManager& GetResourceManager();
		RenderManager& GetRenderManager();
		InputManager& GetInputManager();
		TimeManager& GetTimeManager();
		Scene& GetScene();

		void OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event);

	private:
		EventManager m_EventManager = EventManager();
		ResourceManager m_ResourceManager = ResourceManager();
		RenderManager m_RenderManager = RenderManager(m_EventManager, m_ResourceManager);
		InputManager m_InputManager = InputManager(m_RenderManager);
		TimeManager m_TimeManager = TimeManager();
		Scene m_Scene = Scene(*this);

		EventListener<WindowCloseEvent> m_WindowCloseListener;

		bool m_IsRunning = true;
	};
}

#pragma once

#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/TimeManager.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/ScriptRegistry.h"

namespace Tavern
{
	class Event;

	class TAVERN_API Engine
	{
	public:
		Engine();
		~Engine();

		Engine(const Engine& other) = delete;
		Engine& operator=(const Engine& other) = delete;

		void HandleEvents();
		void Update();
		void Render();

		bool IsRunning();

		void SetUpdateEnabled(bool isUpdateEnabled);
		const bool IsUpdateEnabled() const;

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
		bool m_IsUpdateEnabled = true;
	};
}

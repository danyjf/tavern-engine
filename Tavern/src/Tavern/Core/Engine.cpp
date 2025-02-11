#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/TimeManager.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	Engine::Engine()
		: m_EventManager(),
		  m_ResourceManager(),
		  m_RenderManager(m_EventManager, m_ResourceManager),
		  m_InputManager(m_RenderManager),
		  m_TimeManager(),
		  m_Scene(*this),
		  m_WindowCloseListener(m_EventManager, "WindowClose", std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1))
	{
		ScriptRegistry::Get().SetScene(&m_Scene);
		TAVERN_ENGINE_INFO("Engine initialized");
	}

	Engine::~Engine()
	{
		TAVERN_ENGINE_INFO("Engine destroyed");
	}

	void Engine::HandleEvents()
	{
		glfwPollEvents();
		m_EventManager.DispatchEvents();
	}

	void Engine::Update()
	{
		m_TimeManager.Update();

		// Update State
		if (m_IsUpdateEnabled)
		{
			m_Scene.Update();
		}
	}

	void Engine::Render()
	{
		GetRenderManager().Render();
	}

	bool Engine::IsRunning()
	{
		return m_IsRunning;
	}

	void Engine::SetUpdateEnabled(bool isUpdateEnabled)
	{
		m_IsUpdateEnabled = isUpdateEnabled;
	}

	const bool Engine::IsUpdateEnabled() const
	{
		return m_IsUpdateEnabled;
	}

	EventManager& Engine::GetEventManager()
	{
		return m_EventManager;
	}

	ResourceManager& Engine::GetResourceManager()
	{
		return m_ResourceManager;
	}

	RenderManager& Engine::GetRenderManager()
	{
		return m_RenderManager;
	}

	InputManager& Engine::GetInputManager()
	{
		return m_InputManager;
	}

	TimeManager& Engine::GetTimeManager()
	{
		return m_TimeManager;
	}

	Scene& Engine::GetScene()
	{
		return m_Scene;
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
	}
}

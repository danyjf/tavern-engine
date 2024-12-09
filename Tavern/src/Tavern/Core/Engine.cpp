#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Time.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventListener.h"
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
		  m_UIManager(m_RenderManager),
		  m_InputManager(m_RenderManager),
		  m_TimeManager(),
		  m_Scene(*this),
		  m_UserDefinedEntityRegistry(m_Scene),
		  m_WindowCloseListener(std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1))
	{
		m_EventManager.AddListener(EventType::WindowClose, m_WindowCloseListener);
		TAVERN_ENGINE_INFO("Engine initialized");
	}

	Engine::~Engine()
	{
		m_EventManager.RemoveListener(EventType::WindowClose, m_WindowCloseListener);
		TAVERN_ENGINE_INFO("Engine destroyed");
	}

	void Engine::Update()
	{
		m_TimeManager.UpdateTime();

		// Process events
		m_EventManager.DispatchEvents();

		// Update State
		m_Scene.Update();

		glfwPollEvents();
	}

	bool Engine::IsRunning()
	{
		return m_IsRunning;
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

	UIManager& Engine::GetUIManager()
	{
		return m_UIManager;
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

	UserDefinedEntityRegistry& Engine::GetUserDefinedEntityRegistry()
	{
		return m_UserDefinedEntityRegistry;
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event)
	{
		m_IsRunning = false;
	}
}

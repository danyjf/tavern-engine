#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Time.h"
#include "Tavern/Entity.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	// TODO: Create a resource manager

	Engine::Engine()
		: m_EventManager(),
		  m_ResourceManager(),
		  m_RenderManager(m_EventManager),
		  m_InputManager(m_RenderManager),
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

	void Engine::Run()
	{
		while (m_IsRunning)
		{
			Time::UpdateTime();

			// Process events
			m_EventManager.DispatchEvents();

			// Update State
			for (std::unique_ptr<Entity>& entity : m_Entities)
			{
				entity->Update();
			}

			// Render
			m_RenderManager.Render();

			glfwPollEvents();
			glfwSwapBuffers(m_RenderManager.GetWindow()->GetGLFWWindow());
		}
	}

	void Engine::DestroyEntity(Entity* entity)
	{
		for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
		{
			if ((*it).get() == entity)
			{
				m_Entities.erase(it);
				break;
			}
		}
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

	void Engine::OnWindowCloseEvent(const std::shared_ptr<WindowCloseEvent>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}
}

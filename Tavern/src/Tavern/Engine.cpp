#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Events/ApplicationEvent.h"
#include "Events/EventManager.h"
#include "Log.h"

namespace Tavern
{
	Engine::Engine()
	{
		m_Window = std::unique_ptr<Window>(new Window());
	}

	Engine::~Engine()
	{
	}

	void Engine::Init()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_INFO("Initialized engine logger");

		EventManager::Get().AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
		EventManager::Get().AddListener(EventType::WindowResize, std::bind(&Engine::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Window->Init(WindowSettings("My Window", 800, 600));
	}

	void Engine::GameLoop()
	{
		while (m_IsRunning)
		{
			// Process events
			EventManager::Get().ProcessEvents();

			// Update state
			for (Entity& entity : m_Entities)
			{
				entity.Update();
			}

			glfwPollEvents();
			glfwSwapBuffers(m_Window->GetGLFWWindow());
		}
	}

	void Engine::Shutdown()
	{
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}

	void Engine::OnWindowResizeEvent(const std::shared_ptr<Event>& event)
	{
		std::shared_ptr<WindowResizeEvent> windowResizeEvent = std::dynamic_pointer_cast<WindowResizeEvent>(event);
		glViewport(0, 0, windowResizeEvent->width, windowResizeEvent->height);

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", windowResizeEvent->width, windowResizeEvent->height);
	}

	void Engine::AddEntity(Entity& entity)
	{
		m_Entities.push_back(entity);
	}
}

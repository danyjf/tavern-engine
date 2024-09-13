#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Tavern/Core/Engine.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Renderer/RenderManager.h"

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

		EventManager::Get().Init();
		TAVERN_ENGINE_INFO("Initialized event manager");
		EventManager::Get().AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
		EventManager::Get().AddListener(EventType::WindowResize, std::bind(&Engine::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Window->Init(WindowSettings("My Window", 800, 600));
		TAVERN_ENGINE_INFO("Initialized window");

		RenderManager::Get().Init();
		TAVERN_ENGINE_INFO("Initialized render manager");
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
		RenderManager::Get().Shutdown();
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

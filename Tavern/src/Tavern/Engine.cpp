#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Log.h"
#include "Events/EventManager.h"
#include "Events/ApplicationEvent.h"

namespace Tavern
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		Init();
		GameLoop();
		Shutdown();
	}

	void Engine::Init()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_INFO("Initialized engine log");

		EventManager::Get().AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
		EventManager::Get().AddListener(EventType::WindowResize, std::bind(&Engine::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Window = std::unique_ptr<Window>(new Window());
	}

	void Engine::GameLoop()
	{
		while (m_IsRunning)
		{
			// Process events
			EventManager::Get().ProcessEvents();

			// Update state

			// Render
			glfwPollEvents();
			glfwSwapBuffers(m_Window->GetGLFWWindow());
		}
	}

	void Engine::Shutdown()
	{
		glfwTerminate();
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}

	void Engine::OnWindowResizeEvent(const std::shared_ptr<Event>& event)
	{
		//WindowResizeEvent& windowResizeEvent = ()
		std::shared_ptr<WindowResizeEvent> windowResizeEvent = std::dynamic_pointer_cast<WindowResizeEvent>(event);
		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", windowResizeEvent->width, windowResizeEvent->height);
	}
}

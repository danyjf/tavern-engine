#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Entity.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	Engine::Engine()
	{
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

		RenderManager::Get().Init();
		TAVERN_ENGINE_INFO("Initialized render manager");

		EventManager::Get().AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
	}

	void Engine::GameLoop()
	{
		while (m_IsRunning)
		{
			// Process events
			EventManager::Get().ProcessEvents();

			// Update State
			for (Entity* entity : m_Entities)
			{
				entity->Update();
			}

			// Render
			RenderManager::Get().Render();

			glfwPollEvents();
			glfwSwapBuffers(RenderManager::Get().GetWindow()->GetGLFWWindow());
		}
	}

	void Engine::Shutdown()
	{
		RenderManager::Get().Shutdown();
		EventManager::Get().Shutdown();
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}
}

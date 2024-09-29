#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Time.h"
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

		gEventManager.Init();
		TAVERN_ENGINE_INFO("Initialized event manager");

		gRenderManager.Init();
		TAVERN_ENGINE_INFO("Initialized render manager");

		gEventManager.AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
	}

	void Engine::GameLoop()
	{
		while (m_IsRunning)
		{
			Time::UpdateTime();

			// Process events
			gEventManager.DispatchEvents();

			// Update State
			for (Entity* entity : m_Entities)
			{
				entity->Update();
			}

			// Render
			gRenderManager.Render();

			glfwPollEvents();
			glfwSwapBuffers(gRenderManager.GetWindow()->GetGLFWWindow());
		}
	}

	void Engine::Shutdown()
	{
		gRenderManager.Shutdown();
		gEventManager.Shutdown();
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}
}

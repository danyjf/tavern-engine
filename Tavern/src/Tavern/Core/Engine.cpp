#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Time.h"
#include "Tavern/Entity.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Input/InputManager.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	Engine::Engine()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_INFO("Initialized engine logger");

		m_EventManager = std::make_unique<EventManager>();
		TAVERN_ENGINE_INFO("Initialized event manager");

		m_RenderManager = std::make_unique<RenderManager>(m_EventManager.get());
		TAVERN_ENGINE_INFO("Initialized render manager");

		m_InputManager = std::make_unique<InputManager>(m_RenderManager.get());
		TAVERN_ENGINE_INFO("Initialized input manager");

		m_EventManager->AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		while (m_IsRunning)
		{
			Time::UpdateTime();

			// Process events
			m_EventManager->DispatchEvents();

			// Update State
			for (Entity* entity : m_Entities)
			{
				entity->Update();
			}

			// Render
			m_RenderManager->Render();

			glfwPollEvents();
			glfwSwapBuffers(m_RenderManager->GetWindow()->GetGLFWWindow());
		}
	}

	EventManager* Engine::GetEventManager()
	{
		return m_EventManager.get();
	}

	RenderManager* Engine::GetRenderManager()
	{
		return m_RenderManager.get();
	}

	InputManager* Engine::GetInputManager()
	{
		return m_InputManager.get();
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}
}

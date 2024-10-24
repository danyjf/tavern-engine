#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Components/CameraComponent.h"

namespace Tavern
{
	RenderManager::RenderManager(EventManager& eventManager, ResourceManager& resourceManager)
		: m_EventManager(eventManager),
		  m_WindowResizeListener(std::bind(&RenderManager::OnWindowResizeEvent, this, std::placeholders::_1))
	{
		m_Window = std::make_unique<Window>(m_EventManager, WindowSettings("My Window", 800, 600));

		m_EventManager.AddListener(EventType::WindowResize, m_WindowResizeListener);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		TAVERN_ENGINE_INFO("RenderManager initialized");
	}

	RenderManager::~RenderManager()
	{
		glfwTerminate();
		m_EventManager.RemoveListener(EventType::WindowResize, m_WindowResizeListener);
		TAVERN_ENGINE_INFO("RenderManager destroyed");
	}

	Window* RenderManager::GetWindow() const
	{
		return m_Window.get();
	}

	CameraComponent* RenderManager::GetActiveCamera() const
	{
		return m_Camera;
	}

	void RenderManager::SetActiveCamera(CameraComponent* camera)
	{
		m_Camera = camera;
	}

	void RenderManager::AddRenderComponent(RenderComponent* renderComponent)
	{
		m_RenderComponents.insert(renderComponent);
	}

	void RenderManager::RemoveRenderComponent(RenderComponent* renderComponent)
	{
		m_RenderComponents.erase(renderComponent);
	}

	void RenderManager::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GetActiveCamera()->ComputeViewMatrix();

		for (RenderComponent* renderComponent : m_RenderComponents)
		{
			renderComponent->Render();
		}
	}

	void RenderManager::OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent>& event)
	{
		glViewport(0, 0, event->GetWidth(), event->GetHeight());

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", event->GetWidth(), event->GetHeight());
	}
}

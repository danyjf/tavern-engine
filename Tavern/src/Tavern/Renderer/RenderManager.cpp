#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Renderer/Shader.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Components/CameraComponent.h"

namespace Tavern
{
	RenderManager::RenderManager(EventManager* eventManager)
		: m_EventManager(eventManager)
	{
		m_Window = std::make_unique<Window>(m_EventManager, WindowSettings("My Window", 800, 600));

		m_EventManager->AddListener(EventType::WindowResize, std::bind(&RenderManager::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Shader = std::make_unique<Shader>(
			"./Shaders/Shader.vert",
			"./Shaders/Shader.frag"
		);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	RenderManager::~RenderManager()
	{
		glfwTerminate();
	}

	Window* RenderManager::GetWindow() const
	{
		return m_Window.get();
	}

	Shader* RenderManager::GetShader() const
	{
		return m_Shader.get();
	}

	CameraComponent* RenderManager::GetActiveCamera() const
	{
		return m_Camera;
	}

	void RenderManager::SetActiveCamera(CameraComponent* camera)
	{
		m_Camera = camera;
	}

	void RenderManager::AddMeshComponent(MeshComponent* meshComponent)
	{
		m_MeshComponents.push_back(meshComponent);
	}

	void RenderManager::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GetActiveCamera()->ComputeViewMatrix();

		for (MeshComponent* meshComponent : m_MeshComponents)
		{
			meshComponent->Render();
		}
	}

	void RenderManager::OnWindowResizeEvent(const std::shared_ptr<Event>& event)
	{
		std::shared_ptr<WindowResizeEvent> windowResizeEvent = std::dynamic_pointer_cast<WindowResizeEvent>(event);
		glViewport(0, 0, windowResizeEvent->GetWidth(), windowResizeEvent->GetHeight());

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", windowResizeEvent->GetWidth(), windowResizeEvent->GetHeight());
	}
}

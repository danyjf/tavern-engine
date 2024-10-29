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
#include "Tavern/Scene/Entity.h"
#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/LightComponent.h"

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
		MaterialResource* material = renderComponent->GetMaterial().get();
		if (m_RenderComponents.contains(material))
		{
			m_RenderComponents[material].insert(renderComponent);
		}
		else
		{
			m_RenderComponents.emplace(material, std::unordered_set({ renderComponent }));
		}
	}

	void RenderManager::RemoveRenderComponent(RenderComponent* renderComponent)
	{
		MaterialResource* material = renderComponent->GetMaterial().get();
		m_RenderComponents[material].erase(renderComponent);
		if (m_RenderComponents[material].empty())
		{
			m_RenderComponents.erase(material);
		}
	}

	void RenderManager::AddLightComponent(LightComponent* lightComponent)
	{
		m_LightComponents.insert(lightComponent);
	}

	void RenderManager::RemoveLightComponent(LightComponent* lightComponent)
	{
		m_LightComponents.erase(lightComponent);
	}

	void RenderManager::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GetActiveCamera()->ComputeViewMatrix();

		for (auto& pair : m_RenderComponents)
		{
			MaterialResource* material = pair.first;

			material->GetShader()->Use();
			LightComponent* lightComponent = *(m_LightComponents.begin());
			material->GetShader()->SetVec3("lightColor", lightComponent->GetColor());
			material->GetShader()->SetVec3("lightPos", lightComponent->GetOwner()->GetTransform()->GetPosition());

			for (RenderComponent* renderComponent : m_RenderComponents[material])
			{
				renderComponent->Render();
			}
		}
	}

	void RenderManager::OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent>& event)
	{
		glViewport(0, 0, event->GetWidth(), event->GetHeight());

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", event->GetWidth(), event->GetHeight());
	}
}

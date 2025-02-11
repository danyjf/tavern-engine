#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Events/Event.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Resources/ShaderResource.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/LightComponent.h"

namespace Tavern
{
	RenderManager::RenderManager(EventManager& eventManager, ResourceManager& resourceManager)
		: m_EventManager(eventManager),
		  m_Window(std::make_unique<Window>(m_EventManager)),
		  m_WindowResizeListener(eventManager, std::bind(&RenderManager::OnWindowResizeEvent, this, std::placeholders::_1))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		TAVERN_ENGINE_INFO("RenderManager initialized");
	}

	RenderManager::~RenderManager()
	{
		m_Window.reset();
		glfwTerminate();
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
		m_RenderComponents[material].insert(renderComponent);

		ShaderResource* shader = material->GetShader().get();
		m_Materials[shader].insert(material);
	}

	void RenderManager::RemoveRenderComponent(RenderComponent* renderComponent)
	{
		MaterialResource* material = renderComponent->GetMaterial().get();
		ShaderResource* shader = material->GetShader().get();

		m_RenderComponents[material].erase(renderComponent);
		if (m_RenderComponents[material].empty())
		{
			m_RenderComponents.erase(material);
			m_Materials[shader].erase(material);
		}

		if (m_Materials[shader].empty())
		{
			m_Materials.erase(shader);
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
		if (GetActiveCamera())
		{
			GetActiveCamera()->ComputeViewMatrix();
		}

		for (auto& pair : m_Materials)
		{
			ShaderResource* shader = pair.first;
			// Set shader uniforms
			shader->Bind();
			if (shader->GetBuiltInUniforms().contains("view"))
			{
				shader->SetMat4("view", GetActiveCamera()->GetViewMatrix());
			}
			if (shader->GetBuiltInUniforms().contains("projection"))
			{
				shader->SetMat4("projection", GetActiveCamera()->GetProjectionMatrix());
			}
			if (shader->GetBuiltInUniforms().contains("viewPos"))
			{
				shader->SetVec3("viewPos", GetActiveCamera()->GetOwner()->GetTransform()->GetLocalPosition());
			}

			LightComponent* lightComponent = *(m_LightComponents.begin());
			if (shader->GetBuiltInUniforms().contains("lightColor"))
			{
				shader->SetVec3("lightColor", lightComponent->GetColor());
			}
			if (shader->GetBuiltInUniforms().contains("lightPos"))
			{
				shader->SetVec3("lightPos", lightComponent->GetOwner()->GetTransform()->GetPosition());
			}

			for (MaterialResource* material : m_Materials[shader])
			{
				// Set material uniforms
				material->Bind();

				for (int i = 0; i < shader->GetSamplers().size(); i++)
				{
					glActiveTexture(GL_TEXTURE0 + i);
					material->GetTexture(shader->GetSamplers()[i])->Bind();
				}

				for (RenderComponent* renderComponent : m_RenderComponents[material])
				{
					// Set mesh uniforms
					shader->SetMat4("model", renderComponent->GetOwner()->GetTransform()->GetModelMatrix());

					renderComponent->Render();
				}
			}
		}
		glfwSwapBuffers(GetWindow()->GetGLFWWindow());
	}

	void RenderManager::OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent> event)
	{
		glViewport(0, 0, event->GetWidth(), event->GetHeight());
		GetActiveCamera()->SetViewportSize(event->GetWidth(), event->GetHeight());

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", event->GetWidth(), event->GetHeight());
	}
}

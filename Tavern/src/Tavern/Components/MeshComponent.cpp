#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Shader.h"
#include "Tavern/Renderer/Texture.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	MeshComponent::MeshComponent(Engine* engine, Entity* owner)
		: Component(engine, owner)
	{
		m_Shader = GetEngine()->GetRenderManager().GetShader();
		m_IsVisible = true;

		// TODO: I'm adding mesh components to be rendered but never removing them
		GetEngine()->GetRenderManager().AddMeshComponent(this);

		// Create vertex buffer object
		float vertices[] = {
			// vertices       // texture coords
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3,

			4, 7, 5,
			5, 7, 6,

			8, 9, 10,
			10, 11, 8,

			12, 15, 14,
			14, 13, 12,

			16, 17, 18,
			18, 19, 16,

			20, 23, 22,
			22, 21, 20
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Link vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void MeshComponent::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		m_Shader->Use();

		m_Shader->SetMat4("view", GetEngine()->GetRenderManager().GetActiveCamera()->GetViewMatrix());
		m_Shader->SetMat4("projection", GetEngine()->GetRenderManager().GetActiveCamera()->GetProjectionMatrix());
		m_Shader->SetMat4("model", GetOwner()->GetTransformComponent()->GetModelMatrix());

		for (int i = 0; i < m_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			m_Textures[i].Use();
		}

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void MeshComponent::AddTexture(const Texture& texture)
	{
		if (m_Textures.size() == 16)
		{
			TAVERN_ENGINE_ERROR("Failed to add texture. Maximum of 16 textures reached.");
			return;
		}

		m_Textures.push_back(texture);
	}

	bool MeshComponent::IsVisible() const
	{
		return m_IsVisible;
	}

	void MeshComponent::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
	}
}

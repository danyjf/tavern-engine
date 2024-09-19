#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Entity.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Renderer/Texture.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

namespace Tavern
{
	Entity::Entity()
	{
		m_Shader = RenderManager::Get().GetShader();

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

		TAVERN_ENGINE_INFO("Entity Created");
	}

	Entity::~Entity()
	{
	}

	void Entity::Update()
	{
		// Render ----------------------------------
		m_Shader->Use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		m_Shader->SetMat4("model", model);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		m_Shader->SetMat4("view", view);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		m_Shader->SetMat4("projection", projection);

		for (int i = 0; i < m_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			m_Textures[i]->Use();
		}

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void Entity::AddTexture(std::shared_ptr<Texture>& texture)
	{
		if (m_Textures.size() == 16)
		{
			TAVERN_ENGINE_ERROR("Failed to add texture. Maximum of 16 textures reached.");
			return;
		}

		m_Textures.push_back(texture);
	}
}

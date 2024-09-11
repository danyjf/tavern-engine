#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Entity.h"
#include "Log.h"

namespace Tavern
{
	Entity::Entity()
	{
		// Initialize Render Stuff -----------------------------------------------
		// Compile vertex shader
		const char* vertexShaderSource = "#version 460 core\n"
										 "layout (location = 0) in vec3 aPos;\n"
										 "layout (location = 1) in vec3 aColor;\n"
										 "out vec3 ourColor;\n"
										 "void main()\n"
										 "{\n"
										 " gl_Position = vec4(aPos, 1.0);\n"
										 " ourColor = aColor;\n"
										 "}\0";

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Vertex Shader Compilation Failed: {0}", infoLog);
		}

		// Compile fragment shader
		const char* fragmentShaderSource = "#version 460 core\n"
										   "out vec4 FragColor;\n"
										   "in vec3 ourColor;\n"
										   "void main()\n"
										   "{\n"
										   " FragColor = vec4(ourColor, 1.0);\n"
										   "}\0";

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Fragment Shader Compilation Failed: {0}", infoLog);
		}

		// Create shader program
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);

		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Program Linking Failed: {0}", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Create vertex buffer object
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, // bottom left
			0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,  // bottom right
			0.0f, 0.5f, 0.0f, 0.0, 0.0, 1.0	   // top
		};
		unsigned int indices[] = { 0, 1, 2 };

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Link vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		// [x, y, z, r, g, b, x, y, z, r, g, b, ...]
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered
		// VBO as the vertex attribute's bound vertex buffer object so afterwards we
		// can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally
		// modify this VAO, but this rarely happens. Modifying other VAOs requires a
		// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
		// VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		// End Of Render Initialization
		// -----------------------------------------------

		TAVERN_ENGINE_INFO("Entity Created");
	}

	Entity::~Entity()
	{
	}

	void Entity::Update()
	{
		// Render ----------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_ShaderProgram);

		// Draw the triangle
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

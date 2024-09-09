#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Events/ApplicationEvent.h"
#include "Events/EventManager.h"
#include "Log.h"

namespace Tavern
{
	Engine::Engine()
	{
		m_Window = std::unique_ptr<Window>(new Window());
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		Init();
		GameLoop();
		Shutdown();
	}

	void Engine::Init()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_INFO("Initialized engine logger");

		EventManager::Get().AddListener(EventType::WindowClose, std::bind(&Engine::OnWindowCloseEvent, this, std::placeholders::_1));
		EventManager::Get().AddListener(EventType::WindowResize, std::bind(&Engine::OnWindowResizeEvent, this, std::placeholders::_1));

		m_Window->Init(WindowSettings("My Window", 800, 600));
	}

	void Engine::GameLoop()
	{
		// Initialize Render Stuff -----------------------------------------------
		// Compile vertex shader
		const char* vertexShaderSource = "#version 460 core\n"
										 "layout (location = 0) in vec3 aPos;\n"
										 "void main()\n"
										 "{\n"
										 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
										   "void main()\n"
										   "{\n"
										   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Program Linking Failed: {0}", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Create vertex buffer object
		float vertices[] = {
			0.5f, 0.5f, 0.0f,	// top right
			0.5f, -0.5f, 0.0f,	// bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f,	// top left
		};
		unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

		unsigned int VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Link vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

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

		while (m_IsRunning)
		{
			// Process events
			EventManager::Get().ProcessEvents();

			// Update state

			// Render ----------------------------------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw the triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			// glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwPollEvents();
			glfwSwapBuffers(m_Window->GetGLFWWindow());
		}
	}

	void Engine::Shutdown()
	{
	}

	void Engine::OnWindowCloseEvent(const std::shared_ptr<Event>& event)
	{
		m_IsRunning = false;
		TAVERN_ENGINE_TRACE("Window Close Event");
	}

	void Engine::OnWindowResizeEvent(const std::shared_ptr<Event>& event)
	{
		std::shared_ptr<WindowResizeEvent> windowResizeEvent = std::dynamic_pointer_cast<WindowResizeEvent>(event);
		glViewport(0, 0, windowResizeEvent->width, windowResizeEvent->height);

		TAVERN_ENGINE_TRACE("Window Resize Event: ({0}, {1})", windowResizeEvent->width, windowResizeEvent->height);
	}
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/KeyEvent.h"
#include "Tavern/Events/MouseEvent.h"
#include "Tavern/Renderer/Cursor.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	void Window::Init(const WindowSettings& windowSettings)
	{
		m_WindowSettings = windowSettings;

		// Initialize glfw
		TAVERN_ENGINE_INFO("Initializing GLFW");
		int glfwSuccess = glfwInit();
		TAVERN_ENGINE_ASSERT(glfwSuccess, "Failed to initialize GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create glfw window
		TAVERN_ENGINE_INFO("Creating GLFW window");
		m_Window = glfwCreateWindow(windowSettings.Width, windowSettings.Height, windowSettings.Title.c_str(), NULL, NULL);
		TAVERN_ENGINE_ASSERT(window, "Failed to create GLFW window");
		if (m_Window == NULL)
		{
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_WindowSettings);

		// Initialize glad
		TAVERN_ENGINE_INFO("Initializing GLAD");
		int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TAVERN_ENGINE_ASSERT(gladSuccess, "Failed to Initialize GLAD");

		glViewport(0, 0, windowSettings.Width, windowSettings.Height);

		// Set glfw callbacks
		glfwSetFramebufferSizeCallback(
			m_Window, [](GLFWwindow* window, int width, int height) {
				WindowSettings& windowSettings = *(WindowSettings*)glfwGetWindowUserPointer(window);
				windowSettings.Width = width;
				windowSettings.Height = height;

				std::shared_ptr<WindowResizeEvent> event = std::make_shared<WindowResizeEvent>(width, height);
				gEventManager.QueueEvent(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			std::shared_ptr<WindowCloseEvent> event = std::make_shared<WindowCloseEvent>();
			gEventManager.QueueEvent(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), false);
					gEventManager.QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<KeyReleasedEvent> event = std::make_shared<KeyReleasedEvent>(static_cast<Key>(key));
					gEventManager.QueueEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), true);
					gEventManager.QueueEvent(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::shared_ptr<MouseButtonPressedEvent> event = std::make_shared<MouseButtonPressedEvent>(static_cast<Mouse>(button));
					gEventManager.QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<MouseButtonReleasedEvent> event = std::make_shared<MouseButtonReleasedEvent>(static_cast<Mouse>(button));
					gEventManager.QueueEvent(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			std::shared_ptr<MouseMovedEvent> event = std::make_shared<MouseMovedEvent>(xpos, ypos);
			gEventManager.QueueEvent(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			std::shared_ptr<MouseScrolledEvent> event = std::make_shared<MouseScrolledEvent>(xoffset, yoffset);
			gEventManager.QueueEvent(event);
		});

		// Create cursor
		m_Cursor = Cursor(this, false, true);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	GLFWwindow* Window::GetGLFWWindow() const
	{
		return m_Window;
	}

	const WindowSettings& Window::GetWindowSettings() const
	{
		return m_WindowSettings;
	}

	Cursor& Window::GetCursor()
	{
		return m_Cursor;
	}
}

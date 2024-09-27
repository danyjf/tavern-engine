#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/KeyEvent.h"
#include "Tavern/Events/MouseEvent.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	Window::Window()
	{
	}
	Window::~Window()
	{
	}

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
				EventManager::Get().QueueEvent(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			std::shared_ptr<WindowCloseEvent> event = std::make_shared<WindowCloseEvent>();
			EventManager::Get().QueueEvent(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), false);
					EventManager::Get().QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<KeyReleasedEvent> event = std::make_shared<KeyReleasedEvent>(static_cast<Key>(key));
					EventManager::Get().QueueEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), true);
					EventManager::Get().QueueEvent(event);
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
					EventManager::Get().QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<MouseButtonReleasedEvent> event = std::make_shared<MouseButtonReleasedEvent>(static_cast<Mouse>(button));
					EventManager::Get().QueueEvent(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			std::shared_ptr<MouseMovedEvent> event = std::make_shared<MouseMovedEvent>(xpos, ypos);
			EventManager::Get().QueueEvent(event);
		});

		// TODO: Change this, i am just setting the input mode to hide and capture the mouse
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}

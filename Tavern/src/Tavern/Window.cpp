#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/EventManager.h"
#include "Log.h"
#include "Window.h"

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

				EventManager& eventManager = EventManager::Get();

				std::shared_ptr<WindowResizeEvent> event = std::make_shared<WindowResizeEvent>();
				event->width = width;
				event->height = height;
				eventManager.QueueEvent(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			EventManager& eventManager = EventManager::Get();

			std::shared_ptr<WindowCloseEvent> event = std::make_shared<WindowCloseEvent>();
			eventManager.QueueEvent(event);
		});
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}

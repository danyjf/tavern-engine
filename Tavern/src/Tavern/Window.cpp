#include "Window.h"
#include "Log.h"
#include "Core.h"
#include "Events/EventManager.h"
#include "Events/ApplicationEvent.h"

namespace Tavern
{
	Window::Window()
	{
		// Initialize glfw
		TAVERN_ENGINE_INFO("Initializing GLFW");
		int glfwSuccess = glfwInit();
		TAVERN_ENGINE_ASSERT(glfwSuccess, "Failed to initialize GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// I think this is only needed for mac
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// Create glfw window
		TAVERN_ENGINE_INFO("Creating GLFW window");
		m_Window = glfwCreateWindow(800, 600, "Tavern Window", NULL, NULL);
		TAVERN_ENGINE_ASSERT(window, "Failed to create GLFW window");
		if (m_Window == NULL)
		{
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_Window);

		// Initialize glad
		TAVERN_ENGINE_INFO("Initializing GLAD");
		int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TAVERN_ENGINE_ASSERT(gladSuccess, "Failed to Initialize GLAD");

		glViewport(0, 0, 800, 600);

		// Set glfw callbacks
		glfwSetFramebufferSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height)
			{
				EventManager& eventManager = EventManager::Get();

				std::shared_ptr<WindowResizeEvent> event = std::make_shared<WindowResizeEvent>();
				event->width = width;
				event->height = height;
				eventManager.QueueEvent(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				EventManager& eventManager = EventManager::Get();

				std::shared_ptr<WindowCloseEvent> event = std::make_shared<WindowCloseEvent>();
				eventManager.QueueEvent(event);
			}
		);
	}

	Window::~Window()
	{
	}
}

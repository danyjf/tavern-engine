#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Events/KeyEvent.h"
#include "Tavern/Events/MouseEvent.h"
#include "Tavern/Renderer/Cursor.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	Window::Window(EventManager& eventManager, const WindowSettings& windowSettings)
		: m_EventManager(eventManager),
		  m_WindowResizeListener(std::bind(&Window::OnWindowResizeEvent, this, std::placeholders::_1)),
		  m_WindowSettings(windowSettings)
	{
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
		glfwSetWindowUserPointer(m_Window, &m_EventManager);

		// Initialize glad
		TAVERN_ENGINE_INFO("Initializing GLAD");
		int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TAVERN_ENGINE_ASSERT(gladSuccess, "Failed to Initialize GLAD");

		glViewport(0, 0, windowSettings.Width, windowSettings.Height);

		// Set glfw callbacks
		glfwSetFramebufferSizeCallback(
			m_Window, [](GLFWwindow* window, int width, int height) {
				EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
				std::shared_ptr<WindowResizeEvent> event = std::make_shared<WindowResizeEvent>(width, height);
				eventManager.TriggerEvent(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
			std::shared_ptr<WindowCloseEvent> event = std::make_shared<WindowCloseEvent>();
			eventManager.QueueEvent(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), false);
					eventManager.QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<KeyReleasedEvent> event = std::make_shared<KeyReleasedEvent>(static_cast<Key>(key));
					eventManager.QueueEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					std::shared_ptr<KeyPressedEvent> event = std::make_shared<KeyPressedEvent>(static_cast<Key>(key), true);
					eventManager.QueueEvent(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::shared_ptr<MouseButtonPressedEvent> event = std::make_shared<MouseButtonPressedEvent>(static_cast<Mouse>(button));
					eventManager.QueueEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					std::shared_ptr<MouseButtonReleasedEvent> event = std::make_shared<MouseButtonReleasedEvent>(static_cast<Mouse>(button));
					eventManager.QueueEvent(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
			std::shared_ptr<MouseMovedEvent> event = std::make_shared<MouseMovedEvent>(xpos, ypos);
			eventManager.QueueEvent(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			EventManager& eventManager = *(EventManager*)glfwGetWindowUserPointer(window);
			std::shared_ptr<MouseScrolledEvent> event = std::make_shared<MouseScrolledEvent>(xoffset, yoffset);
			eventManager.QueueEvent(event);
		});

		m_EventManager.AddListener(EventType::WindowResize, m_WindowResizeListener);

		m_Cursor = Cursor(this, false, true);
	}

	Window::~Window()
	{
		m_EventManager.RemoveListener(EventType::WindowResize, m_WindowResizeListener);
		glfwDestroyWindow(m_Window);
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

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
		m_WindowSettings.Title = title;
	}

	void Window::OnWindowResizeEvent(const std::shared_ptr<WindowResizeEvent>& event)
	{
		m_WindowSettings.Width = event->GetWidth();
		m_WindowSettings.Height = event->GetHeight();
	}
}

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Events/ApplicationEvent.h"
#include "Tavern/Renderer/Cursor.h"

namespace Tavern
{
	class EventManager;
	class Event;

	struct WindowSettings
	{
		std::string Title;
		int Width;
		int Height;

		WindowSettings(const std::string& title = "Tavern Window", int width = 800, int height = 600)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class TAVERN_API Window
	{
	public:
		Window(EventManager& eventManager, const WindowSettings& windowSettings = WindowSettings());
		~Window();

		GLFWwindow* GetGLFWWindow() const;
		const WindowSettings& GetWindowSettings() const;
		Cursor& GetCursor();
		void SetSize(const int width, const int height);
		void SetTitle(const std::string& title);

		void OnWindowResizeEvent(const std::shared_ptr<Event>& event);

	private:
		EventManager& m_EventManager;
		GLFWwindow* m_Window = nullptr;
		WindowSettings m_WindowSettings;
		Cursor m_Cursor;
		unsigned long m_WindowResizeListenerID;
	};
}

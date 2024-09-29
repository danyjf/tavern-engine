#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Cursor.h"

namespace Tavern
{
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
		Window();
		~Window();

		void Init(const WindowSettings& windowSettings = WindowSettings());
		void Shutdown();

		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		const WindowSettings& GetWindowSettings() const { return m_WindowSettings; }
		Cursor& GetCursor() { return m_Cursor; }

	private:
		GLFWwindow* m_Window;
		WindowSettings m_WindowSettings;
		Cursor m_Cursor;
	};
}

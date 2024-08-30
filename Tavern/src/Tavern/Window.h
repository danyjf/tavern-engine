#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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

	class Window
	{
	public:
		Window();
		~Window();

		void Init(const WindowSettings& windowSettings = WindowSettings());
		void Shutdown();

		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		const WindowSettings& GetWindowSettings() const { return m_WindowSettings; }

	private:
		GLFWwindow* m_Window;
		WindowSettings m_WindowSettings;
	};
}

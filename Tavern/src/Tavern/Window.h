#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tavern
{
	class Window
	{
	public:
		Window();
		~Window();

		GLFWwindow* GetGLFWWindow() { return m_Window; }

	private:
		GLFWwindow* m_Window;
	};
}

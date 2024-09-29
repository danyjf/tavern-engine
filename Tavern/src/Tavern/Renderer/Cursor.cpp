#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Tavern/Renderer/Cursor.h"
#include "Tavern/Renderer/Window.h"

namespace Tavern
{
	Cursor::Cursor(Window* window, bool isVisible, bool isLocked)
		: m_Window(window), m_IsVisible(isVisible), m_IsLocked(isLocked)
	{
		UpdateCursorState();
	}

	bool Cursor::IsVisible()
	{
		return m_IsVisible;
	}

	void Cursor::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
		UpdateCursorState();
	}

	bool Cursor::IsLocked()
	{
		return m_IsLocked;
	}

	void Cursor::SetIsLocked(bool isLocked)
	{
		m_IsLocked = isLocked;
		UpdateCursorState();
	}

	void Cursor::UpdateCursorState()
	{
		if (m_IsLocked)
		{
			glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return;
		}

		if (m_IsVisible)
		{
			glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return;
		}

		glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}

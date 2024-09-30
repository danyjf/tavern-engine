#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Tavern/Input/InputManager.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	InputManager gInputManager;

	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::Init()
	{
		m_Window = gRenderManager.GetWindow();
	}

	void InputManager::Shutdown()
	{
	}

	bool InputManager::IsKeyPressed(const Key key)
	{
		int state = glfwGetKey(m_Window->GetGLFWWindow(), key);
		return state == GLFW_PRESS;
	}

	bool InputManager::IsMouseButtonPressed(const Mouse button)
	{
		int state = glfwGetMouseButton(m_Window->GetGLFWWindow(), button);
		return state == GLFW_PRESS;
	}

	glm::vec2 InputManager::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetGLFWWindow(), &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}
}

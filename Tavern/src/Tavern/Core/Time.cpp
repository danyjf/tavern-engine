#include <GLFW/glfw3.h>

#include "Tavern/Core/Time.h"

namespace Tavern
{
	float Time::m_ElapsedTime = 0.0f;
	float Time::m_DeltaTime = 0.0f;
	float Time::m_LastFrameTime = 0.0f;

	void Time::UpdateTime()
	{
		float currentFrameTime = glfwGetTime();
		m_DeltaTime = currentFrameTime - m_LastFrameTime;
		m_LastFrameTime = currentFrameTime;
		m_ElapsedTime += m_DeltaTime;
	}
}

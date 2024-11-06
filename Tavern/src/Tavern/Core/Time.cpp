#include <GLFW/glfw3.h>

#include "Tavern/Core/Time.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	TimeManager::TimeManager()
	{
		TAVERN_ENGINE_INFO("TimeManager initialized");
	}

	TimeManager::~TimeManager()
	{
		TAVERN_ENGINE_INFO("TimeManager destroyed");
	}

	void TimeManager::UpdateTime()
	{
		float currentFrameTime = glfwGetTime();
		m_DeltaTime = currentFrameTime - m_LastFrameTime;
		m_LastFrameTime = currentFrameTime;
		m_ElapsedTime += m_DeltaTime;
	}
}

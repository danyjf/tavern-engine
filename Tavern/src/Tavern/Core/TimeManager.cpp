#include <GLFW/glfw3.h>

#include "Tavern/Core/TimeManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	TimeManager::TimeManager()
		: m_PreviousTime(0.0f),
		  m_CurrentTime(0.0f),
		  m_DeltaTime(0.0f),
		  m_ElapsedTime(0.0f),
		  m_TimeScale(1.0f)
	{
		TAVERN_ENGINE_INFO("TimeManager initialized");
	}

	TimeManager::~TimeManager()
	{
		TAVERN_ENGINE_INFO("TimeManager destroyed");
	}

	void TimeManager::Update()
	{
		m_PreviousTime = m_CurrentTime;
		m_CurrentTime = glfwGetTime();

		m_DeltaTime = (m_CurrentTime - m_PreviousTime) * m_TimeScale;

		m_ElapsedTime += m_DeltaTime * m_TimeScale;
	}

	const float TimeManager::GetDeltaTime() const
	{
		return m_DeltaTime;
	}

	const float TimeManager::GetElapsedTime() const
	{
		return m_ElapsedTime;
	}

	void TimeManager::SetTimeScale(float timeScale)
	{
		m_TimeScale = timeScale;
	}

	const float TimeManager::GetTimeScale() const
	{
		return m_TimeScale;
	}
}

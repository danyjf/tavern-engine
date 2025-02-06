#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API TimeManager
	{
	public:
		TimeManager();
		~TimeManager();
		TimeManager(TimeManager& copy) = delete;
		TimeManager& operator=(const TimeManager& copy) = delete;

		void Update();

		const float GetDeltaTime() const;

		const float GetElapsedTime() const;

		void SetTimeScale(float timeScale);
		const float GetTimeScale() const;

	private:
		float m_PreviousTime = 0.0f;
		float m_CurrentTime = 0.0f;
		float m_DeltaTime = 0.0f;
		float m_ElapsedTime = 0.0f;
		float m_TimeScale = 1.0f;
	};
}

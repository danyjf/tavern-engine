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

		const float GetElapsedTime() { return m_ElapsedTime; }
		const float GetDeltaTime() { return m_DeltaTime; }

		void UpdateTime();

	private:
		float m_ElapsedTime = 0.0f;
		float m_DeltaTime = 0.0f;
		float m_LastFrameTime = 0.0f;
	};
}

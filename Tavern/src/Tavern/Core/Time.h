#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Time
	{
	public:
		Time() = delete;

		inline static const float GetElapsedTime() { return m_ElapsedTime; }
		inline static const float GetDeltaTime() { return m_DeltaTime; }

		static void UpdateTime();

	private:
		static float m_ElapsedTime;
		static float m_DeltaTime;
		static float m_LastFrameTime;
	};
}

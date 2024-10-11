#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Window;

	class TAVERN_API Cursor
	{
	public:
		Cursor() = default;
		Cursor(Window* window, bool isVisible, bool isLocked);

		bool IsVisible();
		void SetIsVisible(bool isVisible);

		bool IsLocked();
		void SetIsLocked(bool isLocked);

	private:
		Window* m_Window = nullptr;
		bool m_IsVisible = false;
		bool m_IsLocked = true;

		void UpdateCursorState();
	};
}

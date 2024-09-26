#pragma once

#include "Tavern/Events/Event.h"

namespace Tavern
{
	class WindowCloseEvent : public Event
	{
	public:
		const EventType GetEventType() const override { return EventType::WindowClose; }
		const char* GetName() const override { return "WindowClose"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		const EventType GetEventType() const override
		{
			return EventType::WindowResize;
		};
		const char* GetName() const override { return "WindowResize"; }

	private:
		int m_Width = 0;
		int m_Height = 0;
	};
}

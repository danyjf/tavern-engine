#pragma once

#include "Event.h"

namespace Tavern
{
	class WindowCloseEvent : public Event
	{
	public:
		const EventType GetEventType() const override { return EventType::WindowClose; };
		const char* GetName() const override { return "WindowClose"; };
	};

	class WindowResizeEvent : public Event
	{
	public:
		int width = 0;
		int height = 0;

		const EventType GetEventType() const override
		{
			return EventType::WindowResize;
		};
		const char* GetName() const override { return "WindowResize"; };
	};
}

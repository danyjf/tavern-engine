#pragma once

namespace Tavern
{
	enum EventType
	{
		WindowClose, WindowResize
	};

	class Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual const EventType GetEventType() const = 0;
	};
}

#pragma once

#include "Tavern/Events/Event.h"
#include "Tavern/Core/KeyCodes.h"

namespace Tavern
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(Key key, bool isRepeat)
			: m_Key(key), m_IsRepeat(isRepeat) {}

		const Key GetKey() const { return m_Key; }
		bool IsRepeat() const { return m_IsRepeat; }

		const EventType GetEventType() const override { return EventType::KeyPressed; }
		const char* GetName() const override { return "KeyPressed"; }

	private:
		Key m_Key;
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(Key key)
			: m_Key(key) {}

		const Key GetKey() const { return m_Key; }

		const EventType GetEventType() const override { return EventType::KeyReleased; }
		const char* GetName() const override { return "KeyReleased"; }

	private:
		Key m_Key;
	};
}

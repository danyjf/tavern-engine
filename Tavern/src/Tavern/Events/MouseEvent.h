#pragma once

#include "Tavern/Events/Event.h"
#include "Tavern/Input/MouseCodes.h"

namespace Tavern
{
	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(Mouse button)
			: m_Button(button) {}

		const Mouse GetMouseButton() const { return m_Button; }

		const EventType GetEventType() const override { return EventType::MouseButtonPressed; }
		const char* GetName() const override { return "MouseButtonPressed"; }

	private:
		Mouse m_Button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(Mouse button)
			: m_Button(button) {}

		const Mouse GetMouseButton() const { return m_Button; }

		const EventType GetEventType() const override { return EventType::MouseButtonReleased; }
		const char* GetName() const override { return "MouseButtonReleased"; }

	private:
		Mouse m_Button;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float mouseX, float mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY) {}

		const float GetX() const { return m_MouseX; }
		const float GetY() const { return m_MouseY; }

		const EventType GetEventType() const override { return EventType::MouseMoved; }
		const char* GetName() const override { return "MouseMoved"; }

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		const float GetXOffset() const { return m_XOffset; }
		const float GetYOffset() const { return m_YOffset; }

		const EventType GetEventType() const override { return EventType::MouseScrolled; }
		const char* GetName() const override { return "MouseScrolled"; }

	private:
		float m_XOffset;
		float m_YOffset;
	};
}

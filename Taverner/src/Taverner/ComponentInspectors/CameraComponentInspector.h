#pragma once

#include "Taverner/ComponentInspectors/ComponentInspector.h"

namespace Taverner
{
	class CameraComponentInspector : public ComponentInspector
	{
	public:
		virtual void Render(Tavern::Component* component) override;

	private:
		float m_FOV = 45.0f;
		glm::vec2 m_ViewportSize;
		float m_NearClipPlane = 0.1f;
		float m_FarClipPlane = 100.0f;
	};
}

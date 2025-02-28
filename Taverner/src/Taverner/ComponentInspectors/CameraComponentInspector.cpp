#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Tavern/Components/CameraComponent.h>

#include "Taverner/ComponentInspectors/CameraComponentInspector.h"

namespace Taverner
{
	void CameraComponentInspector::Render(Tavern::Component* component)
	{
		Tavern::CameraComponent* camera = static_cast<Tavern::CameraComponent*>(component);
		m_FOV = camera->GetFOV();
		m_ViewportSize = camera->GetViewportSize();
		m_NearClipPlane = camera->GetNearClipPlane();
		m_FarClipPlane = camera->GetFarClipPlane();

		ImGui::Text("Light");
		if (ImGui::DragFloat("FOV", &m_FOV, 0.1f, 0.1f, 359.9f, "%.2f"))
		{
			camera->SetFOV(m_FOV);
		}
		if (ImGui::DragFloat2("Viewport Size", glm::value_ptr(m_ViewportSize), 1.0f, 0.0f, 0.0f, "%.0f"))
		{
			camera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
		}
		if (ImGui::DragFloat("Near Clip Plane", &m_NearClipPlane, 0.1f, 0.1f, 100000.0f, "%.2f"))
		{
			camera->SetNearClipPlane(m_NearClipPlane);
		}
		if (ImGui::DragFloat("Far Clip Plane", &m_FarClipPlane, 0.1f, 0.1f, 100000.0f, "%.2f"))
		{
			camera->SetFarClipPlane(m_FarClipPlane);
		}
	}
}

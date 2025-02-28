#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Tavern/Components/LightComponent.h>

#include "Taverner/ComponentInspectors/LightComponentInspector.h"

namespace Taverner
{
	void LightComponentInspector::Render(Tavern::Component* component)
	{
		Tavern::LightComponent* light = static_cast<Tavern::LightComponent*>(component);
		m_Color = light->GetColor();

		ImGui::Text("Light");
		if (ImGui::ColorPicker3("Color", glm::value_ptr(m_Color)))
		{
			light->SetColor(m_Color);
		}
	}
}

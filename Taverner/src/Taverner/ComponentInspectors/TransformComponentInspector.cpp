#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Tavern/Components/TransformComponent.h>
#include <Tavern/Core/Log.h>

#include "Taverner/ComponentInspectors/TransformComponentInspector.h"

namespace Taverner
{
	void TransformComponentInspector::Render(Tavern::Component* component)
	{
		Tavern::TransformComponent* transform = static_cast<Tavern::TransformComponent*>(component);
		position = transform->GetLocalPosition();
		rotation = transform->GetLocalEulerRotation();
		scale = transform->GetLocalScale();

        ImGui::SeparatorText("Transform");
		if (ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			transform->SetLocalPosition(position);
		}
		if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			transform->SetLocalEulerRotation(rotation);
		}
		if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f, 0.0f, 0.0f, "%.2f"))
		{
			transform->SetLocalScale(scale);
		}
	}
}

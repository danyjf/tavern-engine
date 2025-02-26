#include <imgui.h>

#include "Taverner/ComponentInspectors/TransformComponentInspector.h"

namespace Taverner
{
	void TransformComponentInspector::Render(Tavern::Component* component)
	{
		ImGui::Text("Transform");
	}
}

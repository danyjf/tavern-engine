#include <imgui.h>

#include "Taverner/ComponentInspectors/LightComponentInspector.h"

namespace Taverner
{
	void LightComponentInspector::Render(Tavern::Component* component)
	{
		ImGui::Text("Light");
	}
}

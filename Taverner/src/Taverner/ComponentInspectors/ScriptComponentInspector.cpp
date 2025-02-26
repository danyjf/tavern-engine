#include <imgui.h>

#include "Taverner/ComponentInspectors/ScriptComponentInspector.h"

namespace Taverner
{
	void ScriptComponentInspector::Render(Tavern::Component* component)
	{
		ImGui::Text("Script");
	}
}

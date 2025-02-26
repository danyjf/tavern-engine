#include <imgui.h>

#include "Taverner/ComponentInspectors/CameraComponentInspector.h"

namespace Taverner
{
	void CameraComponentInspector::Render(Tavern::Component* component)
	{
		ImGui::Text("Camera");
	}
}

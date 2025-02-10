#include <imgui.h>

#include <Tavern/Core/Engine.h>

#include "Taverner/InspectorWindow.h"

namespace Taverner
{
	InspectorWindow::InspectorWindow(Tavern::Engine& engine)
		: m_Engine(engine)
	{
	}

	void InspectorWindow::Render()
	{
		if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None))
		{
		}
		ImGui::End();
	}
}
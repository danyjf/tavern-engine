#include <imgui.h>

#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>

#include "Taverner/Windows/SceneWindow.h"

namespace Taverner
{
	SceneWindow::SceneWindow(Tavern::Engine& engine)
		: m_Engine(engine)
	{
	}

	void SceneWindow::Render()
	{
		if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_None))
		{
			if (ImGui::Button("+"))
			{
				TAVERN_INFO("Add Entity");
			}
		}
		ImGui::End();
	}
}
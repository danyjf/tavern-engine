#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/MenuBar.h"

namespace Tavern
{
	void MenuBar::Render()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project"))
				{
				}
				if (ImGui::MenuItem("Open Project"))
				{
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::MenuItem("New C++ Class"))
				{
				}

				if (ImGui::MenuItem("Generate Visual Studio 2022 Project"))
				{
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Play"))
			{
			}

			ImGui::EndMainMenuBar();
		}
	}
}
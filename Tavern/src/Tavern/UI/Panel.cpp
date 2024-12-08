#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/Panel.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	void Panel::Render()
	{
		// Display windows here
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove 
			| ImGuiWindowFlags_NoBringToFrontOnFocus 
			| ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoNavFocus;
		if (ImGui::Begin("Editor", nullptr, windowFlags))
		{
			ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
			ImGuiID dockSpaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockspaceFlags);

			for (std::unique_ptr<UIElement>& uiElement : m_UIElements)
			{
				if (uiElement->IsVisible())
				{
					uiElement->Render();
				}
			}
		}
		ImGui::End();
	}

	UIElement* Panel::AddUIElement(UIElement* uiElement)
	{
		m_UIElements.emplace_back(std::unique_ptr<UIElement>(uiElement));
		return uiElement;
	}
}

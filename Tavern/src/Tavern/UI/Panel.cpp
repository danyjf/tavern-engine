#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/Panel.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	Panel::Panel(const std::string& name, ImGuiWindowFlags windowFlags, bool isDockSpace)
		: m_Name(name), m_WindowFlags(windowFlags), m_IsDockSpace(isDockSpace)
	{
	}

	void Panel::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::Begin(m_Name.c_str(), nullptr, m_WindowFlags))
		{
			m_Size = ImGui::GetContentRegionAvail();
			if (m_IsDockSpace)
			{
				ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
				ImGuiID dockSpaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockspaceFlags);
			}

			for (std::unique_ptr<UIElement>& uiElement : m_UIElements)
			{
				uiElement->Render();
			}
		}
		ImGui::End();
	}

	UIElement* Panel::AddUIElement(UIElement* uiElement)
	{
		m_UIElements.emplace_back(std::unique_ptr<UIElement>(uiElement));
		return uiElement;
	}

	ImVec2 Panel::GetSize()
	{
		return m_Size;
	}
}

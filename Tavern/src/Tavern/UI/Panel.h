#pragma once

#include <imgui.h>

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	class TAVERN_API Panel : public UIElement
	{
	public:
		Panel(const std::string& name, ImGuiWindowFlags windowFlags, bool isDockSpace = false);
		Panel(Panel& copy) = delete;
		Panel& operator=(const Panel& copy) = delete;

		void Render() override;

		UIElement* AddUIElement(UIElement* uiElement);
		ImVec2 GetSize();

	private:
		std::vector<std::unique_ptr<UIElement>> m_UIElements;
		std::string m_Name;
		ImVec2 m_Size;
		ImGuiWindowFlags m_WindowFlags;
		bool m_IsDockSpace;
	};
}

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/Button.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	Button::Button(const std::string& name, ButtonPressedFunction buttonPressedFunction)
		: m_Name(name), m_ButtonPressedFunction(buttonPressedFunction)
	{
	}

	void Button::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::Button(m_Name.c_str()))
		{
			m_ButtonPressedFunction();
		}
	}
}

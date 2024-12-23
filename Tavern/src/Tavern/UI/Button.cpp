#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/Button.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	Button::Button(const std::string& name)
		: m_Name(name)
	{
	}

	void Button::AddOnClickListener(ButtonPressedFunction buttonPressedFunction)
	{
		m_ButtonPressedListeners.push_back(buttonPressedFunction);
	}

	void Button::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::Button(m_Name.c_str()))
		{
			for (ButtonPressedFunction& listener : m_ButtonPressedListeners)
			{
				listener();
			}
		}
	}
}

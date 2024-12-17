#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/MenuBar.h"

namespace Tavern::UI
{
	void MenuBar::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::BeginMainMenuBar())
		{
			for (std::unique_ptr<Menu>& menu : m_Menus)
			{
				menu->Render();
			}

			ImGui::EndMainMenuBar();
		}
	}

	Menu* MenuBar::AddMenu(const std::string& name)
	{
		m_Menus.emplace_back(std::make_unique<Menu>(name));
		return m_Menus.back().get();
	}

	Menu::Menu(const std::string& name)
		: m_Name(name)
	{
	}

	void Menu::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::BeginMenu(m_Name.c_str()))
		{
			for (std::unique_ptr<MenuItem>& menuItem : m_MenuItems)
			{
				menuItem->Render();
			}

			ImGui::EndMenu();
		}
	}

	MenuItem::MenuItem(const std::string& name, ItemPressedFunction itemPressedFunction)
		: m_Name(name), m_ItemPressedFunction(itemPressedFunction)
	{
	}

	MenuItem* Menu::AddMenuItem(const std::string& name, ItemPressedFunction itemPressedFunction)
	{
		m_MenuItems.emplace_back(std::make_unique<MenuItem>(name, itemPressedFunction));
		return m_MenuItems.back().get();
	}

	void MenuItem::Render()
	{
		if (!m_IsVisible)
		{
			return;
		}

		if (ImGui::MenuItem(m_Name.c_str()))
		{
			m_ItemPressedFunction();
		}
	}
}
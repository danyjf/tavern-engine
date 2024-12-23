#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	using ItemPressedFunction = std::function<void()>;

	class TAVERN_API MenuItem : public UIElement
	{
	public:
		MenuItem(const std::string& name);
		void Render() override;

		void AddOnClickListener(ItemPressedFunction itemPressedFunction);

	private:
		std::string m_Name;
		std::vector<ItemPressedFunction> m_ItemPressedListeners;
	};

	class TAVERN_API Menu : public UIElement
	{
	public:
		Menu(const std::string& name);
		Menu(Menu& copy) = delete;
		Menu& operator=(const Menu& copy) = delete;

		void Render() override;
		MenuItem* AddMenuItem(const std::string& name);

	private:
		std::vector<std::unique_ptr<MenuItem>> m_MenuItems;
		std::string m_Name;
	};

	class TAVERN_API MenuBar : public UIElement
	{
	public:
		MenuBar() = default;
		MenuBar(MenuBar& copy) = delete;
		MenuBar& operator=(const MenuBar& copy) = delete;

		void Render() override;
		Menu* AddMenu(const std::string& name);

	private:
		std::vector<std::unique_ptr<Menu>> m_Menus;
	};
}

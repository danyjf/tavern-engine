#pragma once

#include <imgui.h>

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{

	class TAVERN_API Button : public UIElement
	{
	public:
		Button(const std::string& name);
		Button(Button& copy) = delete;
		Button& operator=(const Button& copy) = delete;

		using ButtonPressedFunction = std::function<void()>;
		void AddOnClickListener(ButtonPressedFunction buttonPressedFunction);

		void Render() override;

	private:
		std::string m_Name;
		std::vector<ButtonPressedFunction> m_ButtonPressedListeners;
	};
}

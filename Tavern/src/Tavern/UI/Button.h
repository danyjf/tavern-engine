#pragma once

#include <imgui.h>

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	using ButtonPressedFunction = std::function<void()>;

	class TAVERN_API Button : public UIElement
	{
	public:
		Button(const std::string& name);
		Button(Button& copy) = delete;
		Button& operator=(const Button& copy) = delete;

		void AddOnClickListener(ButtonPressedFunction buttonPressedFunction);

		void Render() override;

	private:
		std::string m_Name;
		std::vector<ButtonPressedFunction> m_ButtonPressedListeners;
	};
}

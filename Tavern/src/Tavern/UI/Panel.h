#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	class TAVERN_API Panel : public UIElement
	{
	public:
		Panel() = default;
		Panel(Panel& copy) = delete;
		Panel& operator=(const Panel& copy) = delete;

		void Render() override;

		UIElement* AddUIElement(UIElement* uiElement);

	private:
		std::vector<std::unique_ptr<UIElement>> m_UIElements;
	};
}

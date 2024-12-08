#include "Tavern/UI/UIElement.h"

namespace Tavern
{
	void UIElement::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
	}

	bool UIElement::IsVisible() const
	{
		return m_IsVisible;
	}
}

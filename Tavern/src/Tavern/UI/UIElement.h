#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API UIElement
	{
	public:
		virtual void Render() = 0;

		void SetIsVisible(bool isVisible);
		bool IsVisible() const;

	protected:
		bool m_IsVisible = true;
	};
}

#pragma once

#include <Tavern/Components/Component.h>

namespace Taverner
{
	class ComponentInspector
	{
	public:
		virtual ~ComponentInspector() = default;

		virtual void Render(Tavern::Component* component) = 0;
	};
}

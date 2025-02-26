#pragma once

#include "Taverner/ComponentInspectors/ComponentInspector.h"

namespace Taverner
{
	class LightComponentInspector : public ComponentInspector
	{
	public:
		virtual void Render(Tavern::Component* component) override;
	};
}

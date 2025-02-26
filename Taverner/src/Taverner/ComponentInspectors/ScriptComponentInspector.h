#pragma once

#include "Taverner/ComponentInspectors/ComponentInspector.h"

namespace Taverner
{
	class ScriptComponentInspector : public ComponentInspector
	{
	public:
		virtual void Render(Tavern::Component* component) override;
	};
}

#pragma once

#include "Taverner/ComponentInspectors/ComponentInspector.h"

namespace Taverner
{
	class TransformComponentInspector : public ComponentInspector
	{
	public:
		virtual void Render(Tavern::Component* component) override;

	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}

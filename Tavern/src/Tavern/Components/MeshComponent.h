#pragma once

#include "Tavern/Components/Component.h"

namespace Tavern
{
	class Entity;

	class MeshComponent : public Component
	{
	public:
		MeshComponent(Entity* owner);
		~MeshComponent();
	};
}

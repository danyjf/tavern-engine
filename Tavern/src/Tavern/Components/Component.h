#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API Component
	{
	public:
		Component() = default;
		Component(Engine* engine, Entity* owner);
		~Component() = default;

		Entity* GetOwner() const;
		Engine* GetEngine() const;

	private:
		Engine* m_Engine;
		Entity* m_Owner;
	};
}

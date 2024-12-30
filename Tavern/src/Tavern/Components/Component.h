#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API Component
	{
	public:
		Component(Engine& engine, Entity* owner);
		virtual ~Component() = default;

		Engine& GetEngine() const;
		Entity* GetOwner() const;

		virtual void Serialize() = 0;

	private:
		Engine& m_Engine;
		Entity* m_Owner = nullptr;
	};
}

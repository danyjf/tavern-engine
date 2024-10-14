#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API Component
	{
	public:
		Component(Engine* engine, Entity* owner);
		virtual ~Component() = default;

		Entity* GetOwner() const;
		Engine* GetEngine() const;

	private:
		Engine* m_Engine = nullptr;
		Entity* m_Owner = nullptr;
	};
}

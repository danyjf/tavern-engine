#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API BaseComponent
	{
	public:
		BaseComponent(Engine* engine, Entity* owner);
		virtual ~BaseComponent() = default;

		Entity* GetOwner() const;
		Engine* GetEngine() const;

	private:
		Engine* m_Engine = nullptr;
		Entity* m_Owner = nullptr;
	};
}

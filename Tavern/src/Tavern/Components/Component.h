#pragma once

#include <nlohmann/json.hpp>

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

		virtual nlohmann::json Serialize() = 0;
		virtual void Deserialize() = 0;

	private:
		Engine& m_Engine;
		Entity* m_Owner = nullptr;
	};
}

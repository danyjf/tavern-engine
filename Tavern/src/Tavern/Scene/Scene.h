#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Engine;
	class Entity;

	class TAVERN_API Scene
	{
	public:
		Scene(Engine& engine);
		~Scene();
		Scene(Scene& copy) = delete;
		Scene& operator=(const Scene& copy) = delete;

		template <typename EntityClass>
		EntityClass* CreateEntity()
		{
			std::unique_ptr<EntityClass> entity = std::make_unique<EntityClass>(m_Engine);
			EntityClass* pEntity = entity.get();
			m_Entities.emplace(entity->GetID(), std::move(entity));
			return pEntity;
		}
		void DestroyEntity(Entity* entity);

		void Update();

	private:
		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
		Engine& m_Engine;
	};
}

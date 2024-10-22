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

		Entity* GetRoot() const;

		template <typename EntityClass>
		EntityClass* CreateEntity(Entity* parent = nullptr)
		{
			if (parent == nullptr)
			{
				parent = GetRoot();
			}

			std::unique_ptr<EntityClass> entity = std::make_unique<EntityClass>(m_Engine);
			entity->SetParent(parent);

			EntityClass* pEntity = entity.get();

			m_Entities.emplace(entity->GetID(), std::move(entity));

			return pEntity;
		}
		void DestroyEntity(Entity* entity);

		void Update();

	private:
		// TODO: this is kinda weird, maybe change the ownership of the child entities 
		// into the parent entities themselves so that it is easier to destroy entities
		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
		std::unique_ptr<Entity> m_RootEntity;
		Engine& m_Engine;
	};
}

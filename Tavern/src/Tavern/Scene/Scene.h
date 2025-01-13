#pragma once

#include <nlohmann/json.hpp>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Engine;
	class Entity;
	class ScriptComponent;

	class TAVERN_API Scene
	{
		friend class ScriptComponent;

	public:
		Scene(Engine& engine);
		~Scene();
		Scene(Scene& copy) = delete;
		Scene& operator=(const Scene& copy) = delete;

		void SetName(const std::string& name);
		const std::string& GetName() const;

		Entity* GetRoot() const;

		//template <typename T>
		//T* CreateEntity(Entity* parent = nullptr)
		//{
		//	if (parent == nullptr)
		//	{
		//		parent = GetRoot();
		//	}

		//	std::unique_ptr<T> entity = std::make_unique<T>(m_Engine);
		//	entity->SetParent(parent);

		//	T* pEntity = entity.get();

		//	m_Entities.emplace(entity->GetID(), std::move(entity));

		//	return pEntity;
		//}
		Entity* CreateEntity(Entity* parent = nullptr);
		void DestroyEntity(Entity* entity);

		void Update();

		nlohmann::json Serialize();
		void Deserialize();

	private:
		std::string m_Name = "Default";
		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
		std::unique_ptr<Entity> m_RootEntity;
		Engine& m_Engine;
		std::vector<ScriptComponent*> m_Scripts;

		void AddScriptComponent(ScriptComponent* script);
		void RemoveScriptComponent(ScriptComponent* script);
	};
}

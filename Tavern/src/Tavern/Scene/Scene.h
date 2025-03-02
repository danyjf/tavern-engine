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

		Entity* CreateEntity(Entity* parent = nullptr, const std::string& name = "Default");
		void DestroyEntity(Entity* entity);
		Entity* GetEntity(unsigned long id);
		std::unordered_map<unsigned long, std::unique_ptr<Entity>>& GetEntities();

		void Clear();

		void Update();

		nlohmann::ordered_json ToJson();
		void FromJson(const nlohmann::ordered_json& data);

		void Save(const std::string& path);
		void Load(const std::string& path);

	private:
		Engine& m_Engine;
		std::string m_Name = "Default";
		unsigned long m_EntityID = 0;
		Entity* m_Root = nullptr;
		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
		std::vector<ScriptComponent*> m_Scripts;

		void AddScriptComponent(ScriptComponent* script);
		void RemoveScriptComponent(ScriptComponent* script);
	};
}

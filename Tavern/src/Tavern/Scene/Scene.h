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

		Entity* CreateEntity(Entity* parent = nullptr);
		void DestroyEntity(Entity* entity);

		void Update();

		nlohmann::json Serialize();
		void Deserialize();

	private:
		std::string m_Name = "Default";
		std::unordered_map<unsigned long, std::unique_ptr<Entity>> m_Entities = {};
		Engine& m_Engine;
		std::vector<ScriptComponent*> m_Scripts;

		void AddScriptComponent(ScriptComponent* script);
		void RemoveScriptComponent(ScriptComponent* script);
	};
}

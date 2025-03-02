#include <nlohmann/json.hpp>

#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Components/ScriptComponent.h"

namespace Tavern
{
	Scene::Scene(Engine& engine)
		: m_Engine(engine),
		  m_Name("Default")
	{
		TAVERN_ENGINE_INFO("Scene initialized");
	}

	Scene::~Scene()
	{
		TAVERN_ENGINE_INFO("Scene destroyed");
	}

	void Scene::SetName(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& Scene::GetName() const
	{
		return m_Name;
	}

	Entity* Scene::CreateEntity(Entity* parent, const std::string& name)
	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>(m_Engine, parent, name);
		Entity* pEntity = entity.get();

		m_Entities.emplace(entity->GetID(), std::move(entity));

		return pEntity;
	}

	void Scene::DestroyEntity(Entity* entity)
	{
		if (!m_Entities.contains(entity->GetID()))
		{
			TAVERN_ENGINE_WARN("Tried to destroy entity, but entity does not exist");
			return;
		}

		if (entity->m_Parent)
		{
			entity->m_Parent->RemoveChild(entity);
		}

		for (Entity* child : entity->m_Children)
		{
			m_Entities.erase(child->GetID());
		}

		m_Entities.erase(entity->GetID());
	}

	Entity* Scene::GetEntity(unsigned long id)
	{
		if (m_Entities.contains(id))
		{
			return m_Entities[id].get();
		}
		return nullptr;
	}

	std::unordered_map<unsigned long, std::unique_ptr<Entity>>& Scene::GetEntities()
	{
		return m_Entities;
	}

	void Scene::Clear()
	{
		m_Entities.clear();
	}

	void Scene::Update()
	{
		for (ScriptComponent* script : m_Scripts)
		{
			script->Update();
		}
	}

	nlohmann::json Scene::ToJson()
	{
		nlohmann::json json;
		json["name"] = m_Name;
		for (const auto& [id, entity] : m_Entities)
		{
			json["entities"].push_back(entity->ToJson());
		}
		return json;
	}

	void Scene::FromJson(const nlohmann::json& data)
	{
		m_Name = data["name"];

		for (const nlohmann::json& entityData : data["entities"])
		{
			Entity* entity = CreateEntity();
			entity->FromJson(entityData);
		}

		for (const nlohmann::json& entityData : data["entities"])
		{
			if (entityData["parent"] != -1)
			{
				GetEntity(entityData["id"])->SetParent(GetEntity(entityData["parent"]));
			}
		}
	}

	void Scene::Save(const std::string& path)
	{
		std::ofstream saveSceneFile(
			path,
			std::ofstream::out | std::ofstream::trunc
		);
		saveSceneFile << std::setw(2) << ToJson();	// setw(2) sets indentation for pretty printing
		saveSceneFile.close();
	}

	void Scene::Load(const std::string& path)
	{
		Clear();

		std::ifstream sceneFile(path);
		FromJson(nlohmann::json::parse(sceneFile));
		sceneFile.close();
	}

	void Scene::AddScriptComponent(ScriptComponent* script)
	{
		m_Scripts.push_back(script);
	}

	void Scene::RemoveScriptComponent(ScriptComponent* script)
	{
		auto position = std::find(m_Scripts.begin(), m_Scripts.end(), script);
		if (position != m_Scripts.end())
		{
			m_Scripts.erase(position);
		}
	}
}

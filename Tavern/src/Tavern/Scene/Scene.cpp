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
		m_Root = CreateEntity(nullptr, "Root");
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
		Entity* entity = nullptr;
		if (!parent)
		{
			entity = new Entity(m_Engine, m_EntityID, m_Root, name);
		}
		else
		{
			entity = new Entity(m_Engine, m_EntityID, parent, name);
		}
		m_Entities.emplace(m_EntityID, entity);
		m_EntityID++;

		return entity;
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
		m_Root = nullptr;
		m_EntityID = 0;
	}

	void Scene::Update()
	{
		for (ScriptComponent* script : m_Scripts)
		{
			script->Update();
		}
	}

	nlohmann::ordered_json Scene::ToJson()
	{
		nlohmann::ordered_json json;
		json["name"] = m_Name;
		json["scene"] = m_Root->ToJson();
		return json;
	}

	void Scene::FromJson(const nlohmann::ordered_json& data)
	{
		Clear();

		m_Name = data["name"];
		m_Root = CreateEntity();
		m_Root->FromJson(data["scene"]);
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
		std::ifstream sceneFile(path);
		FromJson(nlohmann::ordered_json::parse(sceneFile));
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

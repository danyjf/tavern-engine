#include <nlohmann/json.hpp>

#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	Scene::Scene(Engine& engine)
		: m_Engine(engine),
		  m_Name("Default"),
		  m_RootEntity(std::make_unique<Entity>(engine))
	{
		TAVERN_ENGINE_INFO("Scene created");
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

	Entity* Scene::GetRoot() const
	{
		return m_RootEntity.get();
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

	void Scene::Update()
	{
		for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
		{
			(*it).second->Update();
		}
	}

	nlohmann::json Scene::Serialize()
	{
		nlohmann::json json;
		json["name"] = m_Name;
		for (const auto& [id, entity] : m_Entities)
		{
			json["entities"].push_back(entity->Serialize());
		}
		return json;
	}

	void Scene::Deserialize()
	{

	}
}

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
		  m_Name("Default"),
		  m_RootEntity(std::make_unique<Entity>(engine))
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

	Entity* Scene::GetRoot() const
	{
		return m_RootEntity.get();
	}

	Entity* Scene::CreateEntity(Entity* parent)
	{
		if (parent == nullptr)
		{
			parent = GetRoot();
		}

		std::unique_ptr<Entity> entity = std::make_unique<Entity>(m_Engine);
		entity->SetParent(parent);

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

	void Scene::Update()
	{
		//for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
		//{
		//	(*it).second->Update();
		//}
		for (ScriptComponent* script : m_Scripts)
		{
			script->Update();
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

	void Scene::AddScriptComponent(ScriptComponent* script)
	{
		m_Scripts.push_back(script);
	}

	void Scene::RemoveScriptComponent(ScriptComponent* script)
	{
		m_Scripts.erase(std::remove(m_Scripts.begin(), m_Scripts.end(), script), m_Scripts.end());
	}
}

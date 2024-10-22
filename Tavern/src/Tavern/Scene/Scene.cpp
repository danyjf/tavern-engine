#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	Scene::Scene(Engine& engine)
		: m_Engine(engine)
	{
		TAVERN_ENGINE_INFO("Scene created");
	}

	Scene::~Scene()
	{
		TAVERN_ENGINE_INFO("Scene destroyed");
	}

	void Scene::DestroyEntity(Entity* entity)
	{
		if (!m_Entities.contains(entity->GetID()))
		{
			TAVERN_ENGINE_WARN("Tried to destroy entity, but entity does not exist");
			return;
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
}

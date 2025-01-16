#include "Tavern/Scene/ScriptRegistry.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Components/ScriptComponent.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	ScriptRegistry& ScriptRegistry::Get()
	{
		static ScriptRegistry registry;
		return registry;
	}

	ScriptRegistry::ScriptRegistry()
	{
		TAVERN_ENGINE_INFO("ScriptRegistry initialized");
	}

	ScriptRegistry::~ScriptRegistry()
	{
		TAVERN_ENGINE_INFO("ScriptRegistry destroyed");
	}

	void ScriptRegistry::Register(const std::string& name, CreatorFunction createEntityFunction)
	{
		m_Registry[name] = createEntityFunction;
	}

	ScriptComponent* ScriptRegistry::Create(const std::string& name, Entity* attachToEntity)
	{
		if (!m_Registry.contains(name))
		{
			TAVERN_ENGINE_ERROR("Error creating entity {}. Entity not registered", name);
			return nullptr;
		}
		return m_Registry[name](attachToEntity);
	}

	void ScriptRegistry::SetScene(Scene* scene)
	{
		m_Scene = scene;
	}

	Scene* ScriptRegistry::GetScene() const
	{
		return m_Scene;
	}
}

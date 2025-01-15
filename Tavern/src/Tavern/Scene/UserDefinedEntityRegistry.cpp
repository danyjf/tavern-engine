#include "Tavern/Scene/UserDefinedEntityRegistry.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Components/ScriptComponent.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	UserDefinedEntityRegistry& UserDefinedEntityRegistry::Get()
	{
		static UserDefinedEntityRegistry registry;
		return registry;
	}

	UserDefinedEntityRegistry::UserDefinedEntityRegistry()
	{
		TAVERN_ENGINE_INFO("UserDefineEntityRegistry initialized");
	}

	UserDefinedEntityRegistry::~UserDefinedEntityRegistry()
	{
		TAVERN_ENGINE_INFO("UserDefineEntityRegistry destroyed");
	}

	void UserDefinedEntityRegistry::Register(const std::string& name, CreatorFunction createEntityFunction)
	{
		m_Registry[name] = createEntityFunction;
	}

	ScriptComponent* UserDefinedEntityRegistry::Create(const std::string& name, Entity* attachToEntity)
	{
		if (!m_Registry.contains(name))
		{
			TAVERN_ENGINE_ERROR("Error creating entity {}. Entity not registered", name);
			return nullptr;
		}
		return m_Registry[name](attachToEntity);
	}

	void UserDefinedEntityRegistry::SetScene(Scene* scene)
	{
		m_Scene = scene;
	}

	Scene* UserDefinedEntityRegistry::GetScene() const
	{
		return m_Scene;
	}
}

#include "Tavern/Scene/UserDefinedEntityRegistry.h"
#include "Tavern/Scene/Scene.h"
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
		TAVERN_ENGINE_INFO("UserDefineEntityRegistry created");
	}

	UserDefinedEntityRegistry::~UserDefinedEntityRegistry()
	{
		TAVERN_ENGINE_INFO("UserDefineEntityRegistry destroyed");
	}

	void UserDefinedEntityRegistry::Register(const std::string& name, CreatorFunction createEntityFunction)
	{
		m_Registry[name] = createEntityFunction;
	}

	Entity* UserDefinedEntityRegistry::Create(const std::string& name)
	{
		if (!m_Registry.contains(name))
		{
			TAVERN_ENGINE_ERROR("Error creating entity {}. Entity not registered", name);
			return nullptr;
		}
		return m_Registry[name]();
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

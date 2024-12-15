#include "Tavern/Scene/UserDefinedEntityRegistry.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
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

	void UserDefinedEntityRegistry::SetScene(Scene* scene)
	{
		m_Scene = scene;
	}
}

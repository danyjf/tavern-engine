#include "Tavern/Core/Log.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/ResourceManager.h"

namespace Tavern
{
	Resource::Resource(ResourceManager& resourceManager, const std::string& path)
		: m_ResourceManager(resourceManager), m_Path(path)
	{
		TAVERN_ENGINE_TRACE("Created resource: {}", m_Path);
	}

	Resource::~Resource()
	{
		m_ResourceManager.ResourceHasBeenFreed(m_Path);
		TAVERN_ENGINE_TRACE("Destroyed resource: {}", m_Path);
	}
}

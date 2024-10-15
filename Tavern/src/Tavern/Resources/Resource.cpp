#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/ResourceManager.h"

namespace Tavern
{
	Resource::Resource(ResourceManager& resourceManager, const std::string& path)
		: m_ResourceManager(resourceManager), m_Path(path)
	{
	}

	Resource::~Resource()
	{
		m_ResourceManager.ResourceHasBeenFreed(m_Path);
	}
}

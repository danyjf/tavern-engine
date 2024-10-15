#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	ResourceManager::ResourceManager()
	{
		TAVERN_ENGINE_INFO("ResourceManager initialized");
	}

	ResourceManager::~ResourceManager()
	{
		TAVERN_ENGINE_INFO("ResourceManager destroyed");
	}

	void ResourceManager::ResourceHasBeenFreed(const std::string& path)
	{
		auto it = m_Resources.find(path);
		if (it == m_Resources.end())
		{
			TAVERN_ENGINE_ERROR("Tried to free non existing resource: {}", path);
			return;
		}
		m_Resources.erase(it);
	}
}

#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/TextureResource.h"
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

	std::shared_ptr<TextureResource> ResourceManager::LoadTexture(const std::string& path, const TextureSettings& textureSettings)
	{
		if (m_Resources.contains(path))
		{
			return std::dynamic_pointer_cast<TextureResource>(m_Resources[path].lock());
		}

		std::shared_ptr<TextureResource> resource = std::make_shared<TextureResource>(*this, path, textureSettings);
		m_Resources[path] = resource;

		return resource;
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

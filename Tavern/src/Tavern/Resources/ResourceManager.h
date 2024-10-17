#pragma once

#include <memory>
#include <unordered_map>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/TextureResource.h"

namespace Tavern
{
	class TAVERN_API ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		ResourceManager(ResourceManager& copy) = delete;
		ResourceManager& operator=(const ResourceManager& copy) = delete;

		std::shared_ptr<TextureResource> LoadTexture(const std::string& path, const TextureSettings& textureSettings = TextureSettings());

		template <typename T>
		std::shared_ptr<T> GetResource(const std::string& path)
		{
			if (m_Resources.contains(path))
			{
				return std::dynamic_pointer_cast<T>(m_Resources[path].lock());
			}

			TAVERN_ENGINE_WARN("Tried to get resource not currently loaded: {}", path);
			return nullptr;
		}

		void ResourceHasBeenFreed(const std::string& path);

	private:
		std::unordered_map<std::string, std::weak_ptr<Resource>> m_Resources;
	};
}

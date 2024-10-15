#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	class TAVERN_API ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		ResourceManager(ResourceManager& copy) = delete;
		ResourceManager& operator=(const ResourceManager& copy) = delete;

		template <typename ResourceClass>
		std::shared_ptr<ResourceClass> Load(const std::string& path)
		{
			if (m_Resources.contains(path))
			{
				return m_Resources[path];
			}

			std::shared_ptr<ResourceClass> resource = std::make_shared<ResourceClass>(path);
			m_Resources.emplace(path, resource);

			return resource;
		}

		void ResourceHasBeenFreed(const std::string& path);

	private:
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;
	};
}

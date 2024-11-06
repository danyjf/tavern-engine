#pragma once

#include <memory>
#include <unordered_map>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/ShaderResource.h"
#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Resources/MaterialResource.h"

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
		std::shared_ptr<ShaderResource> LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<MaterialResource> LoadMaterial(const std::string& path);

		void ResourceHasBeenFreed(const std::string& path);

	private:
		std::unordered_map<std::string, std::weak_ptr<TextureResource>> m_TextureResources;
		std::unordered_map<std::string, std::weak_ptr<ShaderResource>> m_ShaderResources;
		std::unordered_map<std::string, std::weak_ptr<MaterialResource>> m_MaterialResources;
	};
}

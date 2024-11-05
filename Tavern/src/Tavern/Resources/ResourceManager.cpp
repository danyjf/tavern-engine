#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Resources/ShaderResource.h"
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
		if (m_TextureResources.contains(path))
		{
			return std::dynamic_pointer_cast<TextureResource>(m_TextureResources[path].lock());
		}

		std::shared_ptr<TextureResource> resource = std::make_shared<TextureResource>(*this, path, textureSettings);
		m_TextureResources[path] = resource;

		return resource;
	}

	std::shared_ptr<ShaderResource> ResourceManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string path = vertexPath + ":" + fragmentPath;
		if (m_ShaderResources.contains(path))
		{
			return std::dynamic_pointer_cast<ShaderResource>(m_ShaderResources[path].lock());
		}

		std::shared_ptr<ShaderResource> resource = std::make_shared<ShaderResource>(*this, vertexPath, fragmentPath);
		m_ShaderResources[path] = resource;

		return resource;
	}

	std::shared_ptr<MaterialResource> ResourceManager::LoadMaterial(const std::string& path, std::shared_ptr<ShaderResource> shader)
	{
		if (m_MaterialResources.contains(path))
		{
			return std::dynamic_pointer_cast<MaterialResource>(m_MaterialResources[path].lock());
		}

		std::shared_ptr<MaterialResource> resource = std::make_shared<MaterialResource>(*this, path, shader);
		m_MaterialResources[path] = resource;

		return resource;
	}

	void ResourceManager::ResourceHasBeenFreed(const std::string& path)
	{
		auto textureIt = m_TextureResources.find(path);
		if (textureIt != m_TextureResources.end())
		{
			m_TextureResources.erase(textureIt);
			return;
		}

		auto shaderIt = m_ShaderResources.find(path);
		if (shaderIt != m_ShaderResources.end())
		{
			m_ShaderResources.erase(shaderIt);
			return;
		}

		auto materialIt = m_MaterialResources.find(path);
		if (materialIt != m_MaterialResources.end())
		{
			m_MaterialResources.erase(materialIt);
			return;
		}

		TAVERN_ENGINE_ERROR("Tried to free non existing resource: {}", path);
	}
}

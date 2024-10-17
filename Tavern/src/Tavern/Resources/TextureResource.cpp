#include <glad/glad.h>
#include <stb_image.h>

#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	TextureResource::TextureResource(ResourceManager& resourceManager, const std::string& path, const TextureSettings& textureSettings)
		: Resource(resourceManager, path), m_TextureSettings(textureSettings)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TextureSettings.textureWrappingS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TextureSettings.textureWrappingT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TextureSettings.textureFilteringMinifying);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TextureSettings.textureFilteringMagnifying);

		stbi_set_flip_vertically_on_load(true);
		int width, height, nrChannels;
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			TAVERN_ENGINE_ERROR("Failed to load texture: {}", path);
		}

		stbi_image_free(textureData);
	}

	void TextureResource::Use()
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}

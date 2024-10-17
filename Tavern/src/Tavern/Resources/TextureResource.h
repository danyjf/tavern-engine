#pragma once

#include <glad/glad.h>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	enum TextureWrapping
	{
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		// TODO: Handle the clamp to border option
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	enum TextureFiltering
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR
	};

	struct TextureSettings
	{
		TextureWrapping textureWrappingS = TextureWrapping::REPEAT;
		TextureWrapping textureWrappingT = TextureWrapping::REPEAT;
		TextureFiltering textureFilteringMinifying = TextureFiltering::LINEAR;
		TextureFiltering textureFilteringMagnifying = TextureFiltering::LINEAR;
	};

	class TAVERN_API TextureResource : public Resource
	{
	public:
		TextureResource(ResourceManager& resourceManager, const std::string& path, const TextureSettings& textureSettings);
		virtual ~TextureResource() override = default;

		void Use();

	private:
		unsigned int m_Texture = 0;
		TextureSettings m_TextureSettings = TextureSettings();
	};
}

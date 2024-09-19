#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	enum TextureWrapping
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		// TODO: Handle the clamp to border option
		CLAMP_TO_BORDER
	};

	enum TextureFiltering
	{
		NEAREST,
		LINEAR
	};

	struct TextureSettings
	{
		TextureWrapping textureWrappingS = TextureWrapping::REPEAT;
		TextureWrapping textureWrappingT = TextureWrapping::REPEAT;
		TextureFiltering textureFilteringMinifying = TextureFiltering::LINEAR;
		TextureFiltering textureFilteringMagnifying = TextureFiltering::LINEAR;
	};

	class TAVERN_API Texture
	{
	public:
		Texture(const TextureSettings& textureSettings, const char* texturePath);
		~Texture();

		void Use();

	private:
		unsigned int m_Texture;
	};
}

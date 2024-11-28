#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class ResourceManager;

	enum FramebufferTextureFormat
	{
		RGBA8,
		RED16,
		DEPTH24STENCIL8
	};

	struct FramebufferTextureSettings
	{
		FramebufferTextureSettings() = default;
		FramebufferTextureSettings(int width, int height, FramebufferTextureFormat format)
			: Width(width), Height(height), Format(format) {}

		int Width = 0;
		int Height = 0;
		FramebufferTextureFormat Format = FramebufferTextureFormat::RGBA8;
	};

	struct FramebufferSettings
	{
		int Width = 0;
		int Height = 0;
		FramebufferTextureSettings TextureSettings;
	};

	class TAVERN_API Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(const FramebufferSettings& framebufferSettings);
		~Framebuffer();

		const FramebufferSettings& GetFramebufferSettings() const;
		unsigned int GetTexture() const;

		void Bind();
		void Unbind();

	private:
		unsigned int m_Framebuffer = 0;
		unsigned int m_Texture = 0;
		FramebufferSettings m_FramebufferSettings = FramebufferSettings();
	};
}

#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class ResourceManager;

	enum FramebufferTextureFormat
	{
		NONE,
		RGBA8,
		RED16,
		DEPTH24STENCIL8
	};

	struct FramebufferSettings
	{
		int Width = 0;
		int Height = 0;
		std::vector<FramebufferTextureFormat> TextureFormats;
	};

	class TAVERN_API Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(const FramebufferSettings& framebufferSettings);
		~Framebuffer();

		const FramebufferSettings& GetFramebufferSettings() const;
		const std::vector<unsigned int>& GetColorTextures() const;

		void Bind();
		void Unbind();
		void Resize(int width, int height);

	private:
		unsigned int m_Framebuffer = 0;

		FramebufferSettings m_FramebufferSettings = FramebufferSettings();
		std::vector<FramebufferTextureFormat> m_ColorTextureFormats;
		FramebufferTextureFormat m_DepthTextureFormat = FramebufferTextureFormat::NONE;

		std::vector<unsigned int> m_ColorTextures;
		unsigned int m_DepthTexture = 0;

		void GenerateFramebuffer();
		void AddColorTextureToFramebuffer(int index, GLint internalFormat, int width, int height, GLenum format);
		void AddDepthTextureToFramebuffer(GLint internalFormat, int width, int height, GLenum format, GLenum attachment);
	};
}

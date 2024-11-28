#include <glad/glad.h>

#include "Tavern/Renderer/Framebuffer.h"
#include "Tavern/Resources/TextureResource.h"

namespace Tavern
{
	Framebuffer::Framebuffer(const FramebufferSettings& framebufferSettings)
	{
		glGenFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture, 0);

		const FramebufferTextureSettings& textureSettings = framebufferSettings.TextureSettings;
		switch (textureSettings.Format)
		{
			case FramebufferTextureFormat::RGBA8:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureSettings.Width, textureSettings.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
				break;
			case FramebufferTextureFormat::RED16:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R16, textureSettings.Width, textureSettings.Height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
				break;
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				// TODO: Deal with depth textures
				break;
		}
		
		// Set the list of draw buffers.
		GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, drawBuffers);

		TAVERN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
		glDeleteTextures(1, &m_Texture);
	}

	const FramebufferSettings& Framebuffer::GetFramebufferSettings() const
	{
		return m_FramebufferSettings;
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		glViewport(0, 0, m_FramebufferSettings.Width, m_FramebufferSettings.Height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

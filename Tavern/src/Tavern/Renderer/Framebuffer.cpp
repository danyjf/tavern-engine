#include <glad/glad.h>

#include "Tavern/Renderer/Framebuffer.h"
#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	Framebuffer::Framebuffer(const FramebufferSettings& framebufferSettings)
		: m_Framebuffer(0), m_FramebufferSettings(framebufferSettings)
	{
		const std::vector<FramebufferTextureFormat>& formats = m_FramebufferSettings.TextureFormats;
		for (int i = 0; i < formats.size(); i++)
		{
			const FramebufferTextureFormat& format = formats[i];
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:
					m_ColorTextureFormats.push_back(format);
					break;
				case FramebufferTextureFormat::RED16:
					m_ColorTextureFormats.push_back(format);
					break;
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					m_DepthTextureFormat = format;
					break;
			}
		}

		GenerateFramebuffer();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
		glDeleteTextures(m_ColorTextures.size(), m_ColorTextures.data());
		glDeleteTextures(1, &m_DepthTexture);
	}

	void Framebuffer::GenerateFramebuffer()
	{
		if (m_Framebuffer)
		{
			glDeleteFramebuffers(1, &m_Framebuffer);
			glDeleteTextures(m_ColorTextures.size(), m_ColorTextures.data());
			glDeleteTextures(1, &m_DepthTexture);

			m_ColorTextures.clear();
			m_DepthTexture = 0;
		}

		glGenFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		for (int i = 0; i < m_ColorTextureFormats.size(); i++)
		{
			const FramebufferTextureFormat& format = m_ColorTextureFormats[i];
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:
					AddColorTextureToFramebuffer(i, GL_RGBA8, m_FramebufferSettings.Width, m_FramebufferSettings.Height, GL_RGBA);
					break;
				case FramebufferTextureFormat::RED16:
					AddColorTextureToFramebuffer(i, GL_R16, m_FramebufferSettings.Width, m_FramebufferSettings.Height, GL_RED);
					break;
			}
		}

		switch (m_DepthTextureFormat)
		{
			case FramebufferTextureFormat::NONE:
				break;
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				AddDepthTextureToFramebuffer(GL_DEPTH24_STENCIL8, m_FramebufferSettings.Width, m_FramebufferSettings.Width, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL_ATTACHMENT);
				break;
		}

		if (!m_ColorTextures.empty())
		{
			GLenum drawBuffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorTextures.size(), drawBuffers);
		}
		else
		{
			glDrawBuffer(0);
		}

		TAVERN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::AddColorTextureToFramebuffer(int index, GLint internalFormat, int width, int height, GLenum format)
	{
		unsigned int colorTexture;
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, colorTexture, 0);

		m_ColorTextures.push_back(colorTexture);
	}

	void Framebuffer::AddDepthTextureToFramebuffer(GLint internalFormat, int width, int height, GLenum format, GLenum attachment)
	{
		glGenTextures(1, &m_DepthTexture);
		glBindTexture(GL_TEXTURE_2D, m_DepthTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_INT_24_8, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, m_DepthTexture, 0);
	}

	const FramebufferSettings& Framebuffer::GetFramebufferSettings() const
	{
		return m_FramebufferSettings;
	}

	const std::vector<unsigned int>& Framebuffer::GetColorTextures() const
	{
		return m_ColorTextures;
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

	void Framebuffer::Resize(int width, int height)
	{
		if (width <= 0 || height <= 0)
		{
			TAVERN_ENGINE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}

		m_FramebufferSettings.Width = width;
		m_FramebufferSettings.Height = height;

		GenerateFramebuffer();
	}
}

#pragma once

#include <Tavern/Core/Engine.h>
#include <Tavern/Renderer/Framebuffer.h>

namespace Taverner
{
	class Editor;

	class GameWindow
	{
	public:
		GameWindow(Tavern::Engine& engine);

		void Render();

		Tavern::Framebuffer& GetGameFramebuffer();

	private:
		Tavern::Engine& m_Engine;

		Tavern::Framebuffer m_GameFramebuffer = Tavern::Framebuffer(
			Tavern::FramebufferSettings(
				800, 
				600, 
				std::vector<Tavern::FramebufferTextureFormat>{
					Tavern::FramebufferTextureFormat::RGBA8, 
					Tavern::FramebufferTextureFormat::DEPTH24STENCIL8
				}
		));
	};
}
#pragma once

#include <Tavern/Renderer/Framebuffer.h>

namespace Taverner
{
	class EditorWindow
	{
	public:
		EditorWindow(Tavern::Engine& engine, Tavern::Window* window, const std::string& title, int width, int height);

		Tavern::Framebuffer& GetGameFramebuffer();

		void Render();

	private:
		Tavern::Engine& m_Engine;
		Tavern::Window* m_Window;
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

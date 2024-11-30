#pragma once

#include <Tavern/Renderer/Framebuffer.h>

namespace Taverner
{
	class EditorWindow
	{
	public:
		EditorWindow(Tavern::Engine& engine, Tavern::Window* window, const std::string& title, int width, int height, Tavern::Framebuffer& gameFramebuffer);

		void Render();

	private:
		Tavern::Engine& m_Engine;
		Tavern::Window* m_Window;
		Tavern::Framebuffer& m_GameFramebuffer;
	};
}

#pragma once

#include <Tavern/Renderer/Framebuffer.h>
#include <nlohmann/json.hpp>

namespace Taverner
{
	class Editor
	{
	public:
		Editor(Tavern::Engine& engine, Tavern::Window* window, const std::string& title, int width, int height);

		Tavern::Framebuffer& GetGameFramebuffer();

		void Render();

	private:
		bool m_IsProjectLoaded = false;
		nlohmann::json m_ProjectConfig;
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

		void CreateNewProject(const std::string& name, const std::string& path);
		void BuildGameProject(const std::string& path);
		void LoadGameDLL(const std::string& path);
	};
}

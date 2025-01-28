#pragma once

#include <nlohmann/json.hpp>

#include <Tavern/Renderer/Framebuffer.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/ProjectConfig.h"

namespace Taverner
{
	class Editor
	{
	public:
		Editor(Tavern::Engine& engine);
		
		void Render();
		Tavern::Framebuffer& GetGameFramebuffer();

	private:
		bool m_ProjectLoaded = false;
		std::string m_EditorPath;
		ProjectConfig m_ProjectConfig;
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

		void CreateNewProject();
		void OpenProject();
		void BuildGameProject(const std::string& path);
		void LoadGame(const std::string& dllPath);
	};
}

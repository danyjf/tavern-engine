#pragma once

#include <Tavern/Renderer/Framebuffer.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/UI/Image.h>
#include <nlohmann/json.hpp>

namespace Taverner
{
	class Editor
	{
	public:
		Editor(Tavern::Engine& engine);
		
		void Update();
		Tavern::Framebuffer& GetGameFramebuffer();

	private:
		Tavern::UI::Panel* m_EditorPanel;
		Tavern::UI::MenuBar* m_MainMenuBar;
		Tavern::UI::Menu* m_FilesMenu;
		Tavern::UI::Menu* m_ToolsMenu;
		Tavern::UI::Menu* m_GameMenu;
		Tavern::UI::Panel* m_GamePanel;
		Tavern::UI::Image* m_GameImage;

		std::string m_EditorPath;
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

		void CreateNewProject();
		void BuildGameProject(const std::string& path);
		void LoadGameDLL(const std::string& path);
	};
}

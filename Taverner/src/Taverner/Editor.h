#pragma once

#include <nlohmann/json.hpp>

#include <Tavern/Renderer/Framebuffer.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/UI/Image.h>
#include <Tavern/UI/FileDialog.h>

#include "Taverner/ProjectConfig.h"

namespace Taverner
{
	class Editor
	{
	public:
		Editor(Tavern::Engine& engine);
		
		void Update();
		Tavern::Framebuffer& GetGameFramebuffer();

	private:
		Tavern::UI::FileDialog* m_OpenProjectFileDialog;

		Tavern::UI::Panel* m_EditorPanel;
		Tavern::UI::Panel* m_ScenePanel;
		Tavern::UI::Panel* m_InspectorPanel;
		Tavern::UI::Panel* m_FileSystemPanel;
		Tavern::UI::Panel* m_GamePanel;

		Tavern::UI::Image* m_GameImage;

		Tavern::UI::MenuBar* m_MainMenuBar;
		Tavern::UI::Menu* m_FilesMenu;
		Tavern::UI::Menu* m_ToolsMenu;
		Tavern::UI::Menu* m_GameMenu;

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

#include <nlohmann/json.hpp>

#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <imgui.h>

#include <Tavern/Renderer/Window.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/UI/Panel.h>
#include <Tavern/UI/MenuBar.h>
#include <Tavern/UI/UIManager.h>
#include <Tavern/UI/Image.h>

#include "Taverner/Editor.h"

using namespace Tavern;

namespace Taverner
{
	Editor::Editor(Engine& engine)
		: m_Engine(engine), 
		 m_Window(engine.GetRenderManager().GetWindow()), 
		 m_EditorPath(std::filesystem::current_path().generic_string())
	{
		m_Window->SetTitle("Unnamed Project");
		m_Window->SetSize(800, 600);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove 
			| ImGuiWindowFlags_NoBringToFrontOnFocus 
			| ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoNavFocus;
		m_EditorPanel = engine.GetUIManager().AddPanel(new UI::Panel("Editor", windowFlags, true));

		m_MainMenuBar = static_cast<UI::MenuBar*>(m_EditorPanel->AddUIElement(new UI::MenuBar()));

		m_FilesMenu = m_MainMenuBar->AddMenu("File");
		m_FilesMenu->AddMenuItem("New Project", std::bind(&Editor::CreateNewProject, this));
		m_FilesMenu->AddMenuItem("Open Project", []() {});

		m_ToolsMenu = m_MainMenuBar->AddMenu("Tools");
		m_ToolsMenu->AddMenuItem("New C++ Class", []() {
			// TODO:
			// Create c++ files
			// Add files to CMakeLists
			// Build DLL
		});
		m_ToolsMenu->AddMenuItem("Generate Visual Studio 2022 Project", [this]() {
			std::string generateCmd = "cmake -S " + (std::string)m_ProjectConfig["projectPath"] + " -B " + (std::string)m_ProjectConfig["projectPath"] + "/VisualStudioProject -G \"Visual Studio 17 2022\" -A x64";
			system(generateCmd.c_str());
		});
		m_ToolsMenu->SetIsVisible(false);

		m_GameMenu = m_MainMenuBar->AddMenu("Game");
		m_GameMenu->AddMenuItem("Play", [this]() {
			BuildGameProject((std::string)m_ProjectConfig["projectPath"] + "/VisualStudioProject");
			LoadGameDLL(m_ProjectConfig["gameDLL"]);
			// Spawn in a cube entity
		});
		m_GameMenu->AddMenuItem("Pause", []() {});
		m_GameMenu->SetIsVisible(false);

		m_EditorPanel->AddUIElement(new UI::Panel("Scene", ImGuiWindowFlags_None));
		m_EditorPanel->AddUIElement(new UI::Panel("Inspector", ImGuiWindowFlags_None));
		m_EditorPanel->AddUIElement(new UI::Panel("File System", ImGuiWindowFlags_None));
		m_GamePanel = static_cast<UI::Panel*>(m_EditorPanel->AddUIElement(new UI::Panel("Game", ImGuiWindowFlags_None)));
		m_GameImage = static_cast<UI::Image*>(m_GamePanel->AddUIElement(new UI::Image(0, ImVec2(100.0f, 100.0f))));
	}

	void Editor::Update()
	{
		ImVec2 viewportPanelSize = m_GamePanel->GetSize();

		const FramebufferSettings& settings = m_GameFramebuffer.GetFramebufferSettings();
		if (viewportPanelSize.x > 0.0f && viewportPanelSize.y > 0.0f &&
			(viewportPanelSize.x != settings.Width || viewportPanelSize.y != settings.Height))
		{
			m_GameFramebuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
			m_Engine.GetRenderManager().GetActiveCamera()->SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
		}

		unsigned int textureID = m_GameFramebuffer.GetColorTextures()[0];
		m_GameImage->SetTextureID((ImTextureID)textureID);
		m_GameImage->SetSize(viewportPanelSize);
	}

	Framebuffer& Editor::GetGameFramebuffer()
	{
		return m_GameFramebuffer;
	}

	void Editor::CreateNewProject()
	{
		// Get name and path of project
		std::string name = "EditorTestProject";
		std::string path = "../../..";

		std::string projectPath = path + "/" + name;
		std::filesystem::create_directories(projectPath);
		std::ofstream cMakeListsFile(
			projectPath + "/CMakeLists.txt",
			std::ofstream::out | std::ofstream::trunc
		);

		cMakeListsFile << "cmake_minimum_required(VERSION 3.30)\n\n"
						  "project(" + name + ")\n\n"
						  "set(CMAKE_CXX_STANDARD 20)\n\n"
						  "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
						  "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Binaries)\n"
						  "set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Binaries)\n"
						  "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Binaries)\n\n"
						  "set(SOURCES\n"
						  "    ./Source/Cube.h\n"
						  "    ./Source/Cube.cpp\n"
						  ")\n\n"
						  "add_library(${PROJECT_NAME} SHARED ${SOURCES})\n\n"
						  "target_include_directories(${PROJECT_NAME} PRIVATE\n"
						  "    ../Tavern/src\n"
						  "    ../Tavern/vendor/spdlog/include\n"
						  "    ../Tavern/vendor/Glad/include\n"
						  "    ../Tavern/vendor/GLFW/include\n"
						  "    ../Tavern/vendor/glm/\n"
						  "    ../Tavern/vendor/assimp/include\n"
						  ")\n\n"
						  "target_link_libraries(${PROJECT_NAME} PRIVATE\n"
						  "    " + m_EditorPath + "/Tavernd.lib\n"
						  "	   " + m_EditorPath + "/assimp-vc143-mtd.lib\n"
						  "    " + m_EditorPath + "/glfw3d.lib\n"
						  "    " + m_EditorPath + "/glmd.lib\n"
						  "    " + m_EditorPath + "/zlibstaticd.lib\n"
						  ")\n";

		cMakeListsFile.close();

		// Create a project.config json file
		m_ProjectConfig = {
			{ "name", name },
			{ "projectPath", projectPath },
			{ "gameDLL", "" }
		};

		std::ofstream projectConfigFile(
			projectPath + "/" + name + ".project",
			std::ofstream::out | std::ofstream::trunc
		);
		projectConfigFile << m_ProjectConfig;
		projectConfigFile.close();

		m_ToolsMenu->SetIsVisible(true);
		m_GameMenu->SetIsVisible(true);
	}

	void Editor::BuildGameProject(const std::string& path)
	{
		TAVERN_INFO("Building game dll");
		std::string buildCmd = "cmake --build " + path;
		system(buildCmd.c_str());

		std::string projectPath = (std::string)m_ProjectConfig["projectPath"];
		std::string name = (std::string)m_ProjectConfig["name"];
		std::string gameDLL = std::format("{}/Binaries/Debug/{}.dll", projectPath, name);
		m_ProjectConfig["gameDLL"] = gameDLL;

		std::ofstream projectConfigFile(
			projectPath + "/" + name + ".project",
			std::ofstream::out | std::ofstream::trunc
		);
		projectConfigFile << m_ProjectConfig;
		projectConfigFile.close();
	}

	void Editor::LoadGameDLL(const std::string& path)
	{
		TAVERN_INFO("Loading game dll");
		LoadLibrary(path.c_str());
	}
}

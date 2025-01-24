#include <nlohmann/json.hpp>

#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <imgui.h>
#include <nlohmann/json.hpp>

#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Renderer/Window.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/UI/Panel.h>
#include <Tavern/UI/MenuBar.h>
#include <Tavern/UI/UIManager.h>
#include <Tavern/UI/Image.h>
#include <Tavern/UI/Button.h>
#include <Tavern/UI/FileDialog.h>

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

		IGFD::FileDialogConfig config;
		config.path = ".";
		m_OpenProjectFileDialog = m_EditorPanel->AddUIElement<UI::FileDialog>("Open Project File", ".project", config);
		m_OpenProjectFileDialog->AddOnOkListener(std::bind(&Editor::OpenProject, this));

		m_MainMenuBar = m_EditorPanel->AddUIElement<UI::MenuBar>();

		m_FilesMenu = m_MainMenuBar->AddMenu("File");
		m_FilesMenu->AddMenuItem("New Project")->AddOnClickListener(std::bind(&Editor::CreateNewProject, this));
		m_FilesMenu->AddMenuItem("Open Project")->AddOnClickListener([this]()
		{
			m_OpenProjectFileDialog->Open();
		});
		m_FilesMenu->AddMenuItem("Save")->AddOnClickListener([this]() {
			Scene& scene = m_Engine.GetScene();
			scene.Save(m_ProjectConfig.GetProjectPath() + "/Content/Scenes/" + scene.GetName() + ".scene");
		});

		m_ToolsMenu = m_MainMenuBar->AddMenu("Tools");
		m_ToolsMenu->AddMenuItem("New C++ Class")->AddOnClickListener([]() {
			// TODO:
			// Create c++ files
			// Add files to CMakeLists
			// Build DLL
		});
		m_ToolsMenu->AddMenuItem("Generate Visual Studio 2022 Project")->AddOnClickListener([this]() {
			std::string generateCmd = "cmake -S " + m_ProjectConfig.GetProjectPath() + " -B " + m_ProjectConfig.GetProjectPath() + "/VisualStudioProject -G \"Visual Studio 17 2022\" -A x64";
			system(generateCmd.c_str());
		});
		m_ToolsMenu->SetIsVisible(false);

		m_GameMenu = m_MainMenuBar->AddMenu("Game");
		m_GameMenu->AddMenuItem("Play")->AddOnClickListener([this]() {
			BuildGameProject(m_ProjectConfig.GetProjectPath() + "/VisualStudioProject");
			LoadGame(m_ProjectConfig.GetGameDLLPath());
		});
		m_GameMenu->AddMenuItem("Pause")->AddOnClickListener([]() {});
		m_GameMenu->SetIsVisible(false);

		m_ScenePanel = m_EditorPanel->AddUIElement<UI::Panel>("Scene", ImGuiWindowFlags_None);
		m_ScenePanel->AddUIElement<UI::Button>("+")->AddOnClickListener([this]() {
			TAVERN_INFO("Add entity");
		});

		m_InspectorPanel = m_EditorPanel->AddUIElement<UI::Panel>("Inspector", ImGuiWindowFlags_None);
		m_FileSystemPanel = m_EditorPanel->AddUIElement<UI::Panel>("File System", ImGuiWindowFlags_None);
		m_GamePanel = m_EditorPanel->AddUIElement<UI::Panel>("Game", ImGuiWindowFlags_None);
		m_GameImage = m_GamePanel->AddUIElement<UI::Image>(0, ImVec2(100.0f, 100.0f));
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
						  "    ./Source/Light.h\n"
						  "    ./Source/Light.cpp\n"
						  ")\n\n"
						  "add_library(${PROJECT_NAME} SHARED ${SOURCES})\n\n"
						  "target_include_directories(${PROJECT_NAME} PRIVATE\n"
						  "    ../Tavern/src\n"
						  "    ../Tavern/vendor/spdlog/include\n"
						  "    ../Tavern/vendor/Glad/include\n"
						  "    ../Tavern/vendor/GLFW/include\n"
						  "    ../Tavern/vendor/glm/\n"
						  "    ../Tavern/vendor/assimp/include\n"
						  "    ../Tavern/vendor/imgui\n"
						  "    ../Tavern/vendor/imgui/backends\n"
						  "	   ../Tavern/vendor/ImGuiFileDialog\n"
						  "    ../Tavern/vendor/nlohmann_json/include\n"
						  ")\n\n"
						  "target_link_libraries(${PROJECT_NAME} PRIVATE\n"
						  "    " + m_EditorPath + "/Tavernd.lib\n"
						  ")\n";

		cMakeListsFile.close();

		// Create a project.config json file
		m_ProjectConfig.SetName(name);
		m_ProjectConfig.SetProjectPath(projectPath);
		m_ProjectConfig.SetGameDLLPath(projectPath + "/Binaries/Debug/" + name + ".dll");
		m_ProjectConfig.Save(projectPath + "/" + name + ".project");

		m_ToolsMenu->SetIsVisible(true);
		m_GameMenu->SetIsVisible(true);
	}

	void Editor::OpenProject()
	{
		std::string path = m_OpenProjectFileDialog->GetFilePath();

		m_ProjectConfig.Load(path);
		TAVERN_INFO("Project Name: {}", m_ProjectConfig.GetName());
		TAVERN_INFO("Project Path: {}", m_ProjectConfig.GetProjectPath());
		TAVERN_INFO("Game DLL Path: {}", m_ProjectConfig.GetGameDLLPath());
	}

	void Editor::BuildGameProject(const std::string& path)
	{
		TAVERN_INFO("Building game dll");
		std::string buildCmd = "cmake --build " + path;
		system(buildCmd.c_str());
	}

	void Editor::LoadGame(const std::string& dllPath)
	{
		TAVERN_INFO("Loading game dll");
		LoadLibrary(dllPath.c_str());

		// Spawn in a cube entity
		Entity* cube = m_Engine.GetScene().CreateEntity();
		ScriptComponent* cubeScript = ScriptRegistry::Get().Create("Cube", cube);
		TAVERN_INFO("Script Loaded: {}", cubeScript->GetTypeName());

		Entity* light = m_Engine.GetScene().CreateEntity();
		ScriptComponent* lightScript = ScriptRegistry::Get().Create("Light", light);
		TAVERN_INFO("Script Loaded: {}", lightScript->GetTypeName());
	}
}

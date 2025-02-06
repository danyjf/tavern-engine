#include <nlohmann/json.hpp>

#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuiFileDialog.h>

#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Renderer/Window.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>

#include "Taverner/Editor.h"
#include "Taverner/FileSystemWindow.h"

using namespace Tavern;

namespace Taverner
{
	Editor::Editor(Engine& engine)
		: m_Engine(engine),
		  m_Window(engine.GetRenderManager().GetWindow()), 
		  m_EditorCamera(engine),
		  m_EditorPath(std::filesystem::current_path().generic_string()),
		  m_FileSystemWindow(engine, m_EditorCamera),
		  m_GameWindow(engine)
	{
		m_EditorCamera.AddToScene();

		m_Window->GetCursor().SetIsLocked(false);
		m_Window->GetCursor().SetIsVisible(true);
		m_Window->SetTitle("Unnamed Project");
		m_Window->SetSize(800, 600);

		// Setup ImGui context
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // Enable Multi-Viewports
		io.IniFilename = "imgui.ini";

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;

		// Setup Platform/Renderer backends
		GLFWwindow* glfwWindow = m_Window->GetGLFWWindow();
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	Editor::~Editor()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Editor::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGuiFileDialog::Instance()->Display("OpenProjectFile", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking))
		{			
			if (ImGuiFileDialog::Instance()->IsOk()) 
			{
				OpenProject();
			}
			
			ImGuiFileDialog::Instance()->Close();
		}

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove 
			| ImGuiWindowFlags_NoBringToFrontOnFocus 
			| ImGuiWindowFlags_NoBackground
			| ImGuiWindowFlags_NoNavFocus;
		if (ImGui::Begin("Editor", nullptr, windowFlags))
		{
			ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
			ImGuiID dockSpaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockspaceFlags);

			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New Project"))
					{
						CreateNewProject();
					}

					if (ImGui::MenuItem("Open Project"))
					{
						IGFD::FileDialogConfig config;
						config.path = ".";
						ImGuiFileDialog::Instance()->OpenDialog("OpenProjectFile", "Open Project File", ".project", config);
					}

					if (ImGui::MenuItem("Save"))
					{
						Scene& scene = m_Engine.GetScene();
						scene.Save(m_ProjectConfig.GetProjectPath() + "/Content/Scenes/" + scene.GetName() + ".scene");
					}

					ImGui::EndMenu();
				}

				if (m_ProjectLoaded && ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("New C++ Class"))
					{
						// TODO:
						// Create c++ files
						// Add files to CMakeLists
						// Build DLL
					}

					if (ImGui::MenuItem("Generate Visual Studio 2022 Project"))
					{
						std::string generateCmd = "cmake -S " + m_ProjectConfig.GetProjectPath() + " -B " + m_ProjectConfig.GetProjectPath() + "/VisualStudioProject -G \"Visual Studio 17 2022\" -A x64";
						system(generateCmd.c_str());
					}

					ImGui::EndMenu();
				}

				if (m_ProjectLoaded && ImGui::BeginMenu("Game"))
				{
					if (ImGui::MenuItem("Play"))
					{
						m_EditorState = EditorState::Playing;
						m_Engine.GetTimeManager().SetTimeScale(1.0f);
					}

					if (ImGui::MenuItem("Pause"))
					{
						m_EditorState = EditorState::Paused;
						m_Engine.GetTimeManager().SetTimeScale(0.0f);
					}

					if (ImGui::MenuItem("Stop"))
					{
						m_EditorState = EditorState::Editing;
						// TODO: Restore initial state
						m_Engine.GetTimeManager().SetTimeScale(0.0f);
					}

					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

			if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_None))
			{
				if (ImGui::Button("+"))
				{
					TAVERN_INFO("Add Entity");
				}
			}
			ImGui::End();

			if (ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None))
			{
			}
			ImGui::End();

			m_FileSystemWindow.Render();
			m_GameWindow.Render();
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
	}

	Editor::EditorState Editor::GetEditorState()
	{
		return m_EditorState;
	}

	EditorCamera& Editor::GetEditorCamera()
	{
		return m_EditorCamera;
	}

	GameWindow& Editor::GetGameWindow()
	{
		return m_GameWindow;
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

		m_ProjectLoaded = true;
		m_Window->SetTitle(m_ProjectConfig.GetName());
		m_FileSystemWindow.LoadFileStructure(m_ProjectConfig.GetProjectPath() + "/Content");
	}

	void Editor::OpenProject()
	{
		std::string path = ImGuiFileDialog::Instance()->GetFilePathName(); 

		m_ProjectConfig.Load(path);
		TAVERN_INFO("Project Name: {}", m_ProjectConfig.GetName());
		TAVERN_INFO("Project Path: {}", m_ProjectConfig.GetProjectPath());
		TAVERN_INFO("Game DLL Path: {}", m_ProjectConfig.GetGameDLLPath());

		BuildGameProject(m_ProjectConfig.GetProjectPath() + "/VisualStudioProject");
		LoadGame(m_ProjectConfig.GetGameDLLPath());

		m_Window->SetTitle(m_ProjectConfig.GetName());
		m_FileSystemWindow.LoadFileStructure(m_ProjectConfig.GetProjectPath() + "/Content");

		m_ProjectLoaded = true;
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
	}
}

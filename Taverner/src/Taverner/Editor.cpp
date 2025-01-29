#include <nlohmann/json.hpp>

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <filesystem>

#include <imgui.h>
#include <ImGuiFileDialog.h>
#include <nlohmann/json.hpp>

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
		 m_EditorPath(std::filesystem::current_path().generic_string())
	{
		m_Window->SetTitle("Unnamed Project");
		m_Window->SetSize(800, 600);
	}

	void Editor::Render()
	{
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
						BuildGameProject(m_ProjectConfig.GetProjectPath() + "/VisualStudioProject");
						LoadGame(m_ProjectConfig.GetGameDLLPath());
					}

					if (ImGui::MenuItem("Pause"))
					{
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

			if (ImGui::Begin("Game", nullptr, ImGuiWindowFlags_None))
			{
				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

				const FramebufferSettings& settings = m_GameFramebuffer.GetFramebufferSettings();
				if (viewportPanelSize.x > 0.0f && viewportPanelSize.y > 0.0f &&
					(viewportPanelSize.x != settings.Width || viewportPanelSize.y != settings.Height))
				{
					m_GameFramebuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
					m_Engine.GetRenderManager().GetActiveCamera()->SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
				}

				unsigned int textureID = m_GameFramebuffer.GetColorTextures()[0];
				ImGui::Image(textureID, viewportPanelSize);
			}
			ImGui::End();
		}
		ImGui::End();
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

		// Spawn in a cube entity
		Entity* cube = m_Engine.GetScene().CreateEntity();
		ScriptComponent* cubeScript = ScriptRegistry::Get().Create("Cube", cube);
		TAVERN_INFO("Script Loaded: {}", cubeScript->GetTypeName());

		Entity* light = m_Engine.GetScene().CreateEntity();
		ScriptComponent* lightScript = ScriptRegistry::Get().Create("Light", light);
		TAVERN_INFO("Script Loaded: {}", lightScript->GetTypeName());
	}
}

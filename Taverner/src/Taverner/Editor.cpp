#include <nlohmann/json.hpp>

#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Tavern/Renderer/Window.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/Editor.h"

using namespace Tavern;

namespace Taverner
{
	Editor::Editor(Engine& engine, Window* window, const std::string& title, int width, int height)
		: m_Engine(engine), m_Window(window)
	{
		m_Window->SetTitle(title);
		m_Window->SetSize(width, height);
	}

	Tavern::Framebuffer& Editor::GetGameFramebuffer()
	{
		return m_GameFramebuffer;
	}

	void Editor::Render()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Display windows here
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
						CreateNewProject("EditorTestProject", "C:/Dev/tavern-engine");
					}
					if (ImGui::MenuItem("Open Project"))
					{
					}
					ImGui::EndMenu();
				}
				if (m_IsProjectLoaded && ImGui::BeginMenu("Tools"))
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
						std::string generateCmd = "cmake -S " + (std::string)m_ProjectConfig["projectPath"] + " -B " + (std::string)m_ProjectConfig["projectPath"] + "/VisualStudioProject -G \"Visual Studio 17 2022\" -A x64";
						system(generateCmd.c_str());
					}

					ImGui::EndMenu();
				}

				if (m_IsProjectLoaded && ImGui::MenuItem("Play"))
				{
					BuildGameProject((std::string)m_ProjectConfig["projectPath"] + "/VisualStudioProject");
					LoadGameDLL(m_ProjectConfig["gameDLL"]);
					// Spawn in a cube entity
				}

				ImGui::EndMainMenuBar();
			}

			if (ImGui::Begin("Scene"))
			{
				ImGui::Text("Scene Hierarchy Window");
			}
			ImGui::End();

			if (ImGui::Begin("Inspector"))
			{
				ImGui::Text("Inspector Window");
			}
			ImGui::End();

			if (ImGui::Begin("File System"))
			{
				ImGui::Text("File System Window");
			}
			ImGui::End();

			if (ImGui::Begin("Game"))
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
				ImGui::Image((ImTextureID)textureID, viewportPanelSize);
			}
			ImGui::End();
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
	}

	void Editor::CreateNewProject(const std::string& name, const std::string& path)
	{
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
						  "    C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/Tavernd.lib\n"
						  "    C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/assimp-vc143-mtd.lib\n"
						  "    C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/glfw3d.lib\n"
						  "    C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/glmd.lib\n"
						  "    C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/zlibstaticd.lib\n"
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

		m_IsProjectLoaded = true;
	}

	void Editor::BuildGameProject(const std::string& path)
	{
		// TODO:
		// Build the game dll
		std::string buildCmd = "cmake --build " + path;
		system(buildCmd.c_str());
	}

	void Editor::LoadGameDLL(const std::string& path)
	{
		LoadLibrary(path.c_str());
	}
}

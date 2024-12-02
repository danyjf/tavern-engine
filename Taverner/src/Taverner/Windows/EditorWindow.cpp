#include <Windows.h>
#include <filesystem>
#include <fstream>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Tavern/Renderer/Window.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/Windows/EditorWindow.h"

using namespace Tavern;

namespace Taverner
{
	EditorWindow::EditorWindow(Tavern::Engine& engine, Window* window, const std::string& title, int width, int height, Framebuffer& gameFramebuffer)
		: m_Engine(engine), m_Window(window), m_GameFramebuffer(gameFramebuffer)
	{
		m_Window->SetTitle(title);
		m_Window->SetSize(width, height);
	}

	void EditorWindow::Render()
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
						std::string projectName("EditorTestProject");
						std::string path("C:/Dev/tavern-engine");
						path += "/" + projectName + "/.Taverner";

						// Create CMakeLists.txt to build the project into dll using cmake
						std::filesystem::create_directories(path);
						std::ofstream cMakeListsFile(
							path + "/" + "CMakeLists.txt",
							std::ofstream::out | std::ofstream::trunc
						);

						cMakeListsFile << "cmake_minimum_required(VERSION 3.30)" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "project(" << projectName << ")" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)" << std::endl;
						cMakeListsFile << "set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)" << std::endl;
						cMakeListsFile << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "set(SOURCES" << std::endl;
						cMakeListsFile << "../Cube.h" << std::endl;
						cMakeListsFile << "../Cube.cpp" << std::endl;
						cMakeListsFile << ")" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "add_library(${PROJECT_NAME} SHARED ${SOURCES})" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "target_include_directories(${PROJECT_NAME} PRIVATE" << std::endl;
						cMakeListsFile << "../../Tavern/src" << std::endl;
						cMakeListsFile << "../../Tavern/vendor/spdlog/include" << std::endl;
						cMakeListsFile << "../../Tavern/vendor/Glad/include" << std::endl;
						cMakeListsFile << ")" << std::endl;
						cMakeListsFile << "target_link_libraries(${PROJECT_NAME} PRIVATE" << std::endl;
						cMakeListsFile << "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/Tavernd.lib" << std::endl;
						cMakeListsFile << ")" << std::endl;
						cMakeListsFile << std::endl;

						cMakeListsFile.close();

						// Create a project.config json file
						std::ofstream projectConfigFile(
							path + "/" + "project.config",
							std::ofstream::out | std::ofstream::trunc
						);

						std::string projectConfig = "{\n"
													"    \"name\": \"EditorTestProject\",\n"
													"    \"projectPath\": \"" + path + "\",\n"
													"    \"gameDLL\": \"\"\n"
													"}";

						projectConfigFile << projectConfig;

						projectConfigFile.close();
					}
					if (ImGui::MenuItem("Open Project"))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Tools"))
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
						system("cmake -S C:/Dev/tavern-engine/EditorTestProject/.Taverner -B C:/Dev/tavern-engine/EditorTestProject/.Taverner/Build -G \"Visual Studio 17 2022\" -A x64");
					}

					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Play"))
				{
					// TODO:
					// Build the game dll
					// Spawn in a cube entity
					system("cmake --build C:/Dev/tavern-engine/EditorTestProject/.Taverner/Build");
					//LoadLibrary("C:/Dev/tavern-engine/EditorTestProject/.Taverner/bin/");
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
}

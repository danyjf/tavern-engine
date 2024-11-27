#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Tavern/Renderer/Window.h>

#include "Taverner/Windows/EditorWindow.h"

namespace Taverner
{
	EditorWindow::EditorWindow(Tavern::Window* window, const std::string& title, int width, int height)
	{
		m_Window = window;
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
						path += "/" + projectName;

						// Create CMakeLists.txt to build the project into dll using cmake
						std::filesystem::create_directory(path);
						std::ofstream cMakeListsFile(
							path + "/" + "CMakeLists.txt",
							std::ofstream::out | std::ofstream::trunc
						);

						cMakeListsFile << "cmake_minimum_required(VERSION 3.30)" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "project(" << projectName << ")" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY .taverner/)" << std::endl;
						cMakeListsFile << "set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .taverner/)" << std::endl;
						cMakeListsFile << "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .taverner/)" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "set(SOURCES" << std::endl;
						cMakeListsFile << ")" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "add_library(${PROJECT_NAME} SHARED ${SOURCES})" << std::endl;
						cMakeListsFile << std::endl;
						cMakeListsFile << "target_include_directories(${PROJECT_NAME} PRIVATE" << std::endl;
						cMakeListsFile << "../Tavern/src" << std::endl;
						cMakeListsFile << "../Tavern/vendor/spdlog/include" << std::endl;
						cMakeListsFile << "../Tavern/vendor/Glad/include" << std::endl;
						cMakeListsFile << ")" << std::endl;
						cMakeListsFile << std::endl;

						cMakeListsFile.close();

						// Create a project.config json file
					}
					if (ImGui::MenuItem("Open Project"))
					{
					}
					ImGui::EndMenu();
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

			if (ImGui::Begin("Viewport"))
			{
				ImGui::Text("Viewport Window");
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

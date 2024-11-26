#include <filesystem>
#include <fstream>
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Tavern/Renderer/Window.h>

#include "Taverner/Windows/ProjectWindow.h"

namespace Taverner
{
	ProjectWindow::ProjectWindow(Tavern::Window* window, const std::string& title, int width, int height)
	{
		m_Window = window;
		m_Window->SetTitle(title);
		m_Window->SetSize(width, height);
	}

	void ProjectWindow::Render()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Display windows here
		{
			ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize
										   | ImGuiWindowFlags_NoTitleBar
										   | ImGuiWindowFlags_NoMove
										   | ImGuiWindowFlags_NoScrollbar
										   | ImGuiWindowFlags_NoScrollWithMouse
										   | ImGuiWindowFlags_NoBackground
										   | ImGuiWindowFlags_AlwaysAutoResize
										   | ImGuiWindowFlags_NoCollapse;
			ImGui::SetNextWindowPos(ImVec2(m_Window->GetWindowSettings().Width / 2.0f, m_Window->GetWindowSettings().Height / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
			ImGui::Begin("Project", nullptr, windowFlags);

			// ImGui::Text("Path: ");
			// ImGui::SameLine();
			// char projectPath[512];
			// ImGui::InputText("##1", projectPath, 512);

			std::string projectName("EditorTestProject");
			std::string path("C:/Dev/tavern-engine");
			path += "/" + projectName;

			if (ImGui::Button("Create", ImVec2(75.0, 25.0))) // Buttons return true when clicked (most widgets return true when edited/activated)
			{
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

				m_IsSelectingProject = false;
			}
			ImGui::SameLine(0.0, 20.0);
			if (ImGui::Button("Open", ImVec2(75.0, 25.0)))
			{
			}

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	const bool ProjectWindow::IsSelectingProject() const
	{
		return m_IsSelectingProject;
	}
}

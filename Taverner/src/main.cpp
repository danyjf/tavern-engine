#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Tavern/Core/Engine.h>

int main()
{
	// Setup Tavern Engine
	Tavern::Engine engine(Tavern::WindowSettings("Projects", 500, 350));
	Tavern::Window* window = engine.GetRenderManager().GetWindow();
	window->GetCursor().SetIsLocked(false);
	window->GetCursor().SetIsVisible(true);

	// Setup ImGui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

	bool selectingProject = true;
	// Create/Open project stuff -------------------------------------------------
	while (selectingProject)
	{
		engine.Update();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		engine.GetRenderManager().Render();

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
			ImGui::SetNextWindowPos(ImVec2(window->GetWindowSettings().Width / 2.0f, window->GetWindowSettings().Height / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
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

				selectingProject = false;
			}
			ImGui::SameLine(0.0, 20.0);
			if (ImGui::Button("Open", ImVec2(75.0, 25.0)))
			{
			}

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		engine.GetRenderManager().SwapBuffers();
	}

	window->SetTitle("MyProject");
	window->SetSize(800, 600);
	// Game stuff --------------------------------------------------------------------
	while (engine.IsRunning())
	{
		engine.Update();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		engine.GetRenderManager().Render();

		// Display windows here
		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		engine.GetRenderManager().SwapBuffers();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

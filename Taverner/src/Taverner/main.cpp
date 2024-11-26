#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/Windows/ProjectWindow.h"
#include "Taverner/Windows/EditorWindow.h"

std::string RunProjectWindow(Tavern::Engine& engine, Tavern::Window* window)
{
	Taverner::ProjectWindow projectWindow(window, "Projects", 500, 350);
	while (projectWindow.IsSelectingProject() && engine.IsRunning())
	{
		engine.Update();
		engine.GetRenderManager().Render();

		projectWindow.Render();

		engine.GetRenderManager().SwapBuffers();
	}
	return "ProjectName";
}

void RunEditorWindow(std::string projectName, Tavern::Engine& engine, Tavern::Window* window)
{
	Taverner::EditorWindow editorWindow(window, projectName, 800, 600);
	while (engine.IsRunning())
	{
		engine.Update();
		engine.GetRenderManager().Render();

		editorWindow.Render();

		engine.GetRenderManager().SwapBuffers();
	}
}

int main()
{
	// Setup Tavern Engine
	//Tavern::Engine engine(Tavern::WindowSettings("Projects", 500, 350));
	Tavern::Engine engine;
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

	// TODO: Instead of having two window, just launch with editor window
	// and then let the user use "Open Project"/"Create Project" buttons
	std::string projectName = RunProjectWindow(engine, window);
	RunEditorWindow(projectName, engine, window);

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

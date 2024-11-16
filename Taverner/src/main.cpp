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

	ImVec4 testColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Create/Open project stuff -------------------------------------------------
	while (engine.IsRunning())
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

			if (ImGui::Button("Create", ImVec2(75.0, 25.0))) // Buttons return true when clicked (most widgets return true when edited/activated)
			{
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

#include <imgui.h>
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
		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

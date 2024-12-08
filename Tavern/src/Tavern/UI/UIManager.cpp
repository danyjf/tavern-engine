#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/UIManager.h"
#include "Tavern/UI/UIElement.h"
#include "Tavern/UI/Panel.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Renderer/RenderManager.h"

namespace Tavern
{
	UIManager::UIManager(RenderManager& renderManager)
		: m_RenderManager(renderManager)
	{
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
		GLFWwindow* glfwWindow = m_RenderManager.GetWindow()->GetGLFWWindow();
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 460");
		TAVERN_ENGINE_INFO("UIManager initialized");
	}

	UIManager::~UIManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		TAVERN_ENGINE_INFO("UIManager destroyed");
	}

	void UIManager::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (std::unique_ptr<Panel>& panel : m_Panels)
		{
			if (panel->IsVisible())
			{
				panel->Render();
			}
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
	}

	std::vector<std::unique_ptr<Panel>>& UIManager::GetPanels()
	{
		return m_Panels;
	}

	Panel* UIManager::AddPanel(Panel* panel)
	{
		m_Panels.emplace_back(std::unique_ptr<Panel>(panel));
		return m_Panels.back().get();
	}
}
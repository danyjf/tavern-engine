#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Tavern/Core/Engine.h>

#include "Taverner/Windows/EditorWindow.h"

using namespace Tavern;

int main()
{
	// Setup Tavern Engine
	Engine engine;
	Window* window = engine.GetRenderManager().GetWindow();
	window->GetCursor().SetIsLocked(false);
	window->GetCursor().SetIsVisible(true);

	// Setup ImGui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // Enable Multi-Viewports
	io.IniFilename = "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Taverner/imgui.ini";

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

	FramebufferSettings framebufferSettings;
	framebufferSettings.Width = 1280;
	framebufferSettings.Height = 720;
	framebufferSettings.TextureSettings = FramebufferTextureSettings(1280, 720, FramebufferTextureFormat::RGBA8);
	Framebuffer gameFramebuffer = Framebuffer(framebufferSettings);
	Taverner::EditorWindow editorWindow(window, "Unnamed Project", 800, 600, gameFramebuffer);
	while (engine.IsRunning())
	{
		engine.Update();
		gameFramebuffer.Bind();
		engine.GetRenderManager().Render();
		gameFramebuffer.Unbind();

		editorWindow.Render();

		engine.GetRenderManager().SwapBuffers();
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

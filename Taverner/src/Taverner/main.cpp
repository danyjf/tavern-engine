#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Tavern/Core/Engine.h>
#include <Tavern/Core/Log.h>
#include <Tavern/Core/Core.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/LightComponent.h>
#include <Tavern/UI/Panel.h>
#include <Tavern/UI/MenuBar.h>

#include "Taverner/Editor.h"

using namespace Tavern;

class EditorCamera : public ScriptComponent
{
public:
	EditorCamera(Engine& engine, Entity* owner)
		: ScriptComponent(engine, owner), m_Speed(2.5f), m_Zoom(45.0f)
	{
		m_Camera = GetOwner()->CreateComponentOfType<CameraComponent>();
		GetEngine().GetRenderManager().SetActiveCamera(m_Camera);
	
		GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}

	void Update() override
	{
		glm::vec2 direction(0.0f);
	
		if (GetEngine().GetInputManager().IsKeyPressed(Key::W))
		{
			direction.y += 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::S))
		{
			direction.y -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::A))
		{
			direction.x -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::D))
		{
			direction.x += 1.0f;
		}
	
		glm::vec3 translation = GetOwner()->GetTransform()->GetLocalFrontDirection() * direction.y;
		translation += GetOwner()->GetTransform()->GetLocalRightDirection() * direction.x;
	
		if (glm::length(translation) != 0)
		{
			translation = glm::normalize(translation);
			GetOwner()->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetLocalPosition() + translation * m_Speed * GetEngine().GetTimeManager().GetDeltaTime());
		}
	}

	CameraComponent* GetCamera()
	{
		return m_Camera;
	}

private:
	CameraComponent* m_Camera;
	float m_Speed;
	float m_Zoom;
};
REGISTER_SCRIPT(EditorCamera);

int main()
{
	// Setup Tavern Engine
	//Engine& engine = Engine::Get();
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
	io.IniFilename = "imgui.ini";

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	// Setup Platform/Renderer backends
	GLFWwindow* glfwWindow = window->GetGLFWWindow();
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// TODO: Remove this game code
	Entity* editorCamera = engine.GetScene().CreateEntity();
	ScriptRegistry::Get().Create("EditorCamera", editorCamera);

	Taverner::Editor editor(engine);
	while (engine.IsRunning())
	{
		engine.Update();
		//editor.Update();

		editor.GetGameFramebuffer().Bind();
		engine.GetRenderManager().Render();
		editor.GetGameFramebuffer().Unbind();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		editor.Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);

		engine.GetRenderManager().SwapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

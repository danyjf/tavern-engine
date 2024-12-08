#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/LightComponent.h>
#include <Tavern/UI/Panel.h>
#include <Tavern/UI/MenuBar.h>

#include "Taverner/Editor.h"

class Light : public Tavern::Entity
{
public:
	Light(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		m_StartPosition = glm::vec3(0.0f, 1.0f, -3.0f);
		GetTransform()->SetLocalPosition(m_StartPosition);
		GetTransform()->SetLocalScale(glm::vec3(0.25f));

		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("../EngineTestProject/Assets/Materials/Light.material");
		std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("../EngineTestProject/BuiltInAssets/Meshes/Cube.obj");
		m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
		m_Mesh->SetMesh(mesh);

		m_Light = CreateComponentOfType<Tavern::LightComponent>();
		m_Light->SetColor(glm::vec3(1.0f));
	}

	void Update() override
	{
		Tavern::Entity::Update();

		GetTransform()->SetLocalPosition(glm::vec3(
			m_StartPosition.x + sin(2.0f * GetEngine().GetTimeManager().GetElapsedTime()) / 2.0f * 3.0f,
			m_StartPosition.y,
			m_StartPosition.z + cos(GetEngine().GetTimeManager().GetElapsedTime()) * 3.0f
		));
	}

private:
	Tavern::MeshComponent* m_Mesh;
	Tavern::LightComponent* m_Light;
	glm::vec3 m_StartPosition;
};

class EditorCamera : public Tavern::Entity
{
public:
	EditorCamera(Tavern::Engine& engine)
		: Tavern::Entity(engine), m_Speed(2.5f), m_Zoom(45.0f)
	{
		m_Camera = CreateComponentOfType<Tavern::CameraComponent>();
		GetEngine().GetRenderManager().SetActiveCamera(m_Camera);
	
		GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetTransform()->SetLocalEulerRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}

	void Update() override
	{
		Tavern::Entity::Update();
	
		glm::vec2 direction(0.0f);
	
		if (GetEngine().GetInputManager().IsKeyPressed(Tavern::Key::W))
		{
			direction.y += 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Tavern::Key::S))
		{
			direction.y -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Tavern::Key::A))
		{
			direction.x -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Tavern::Key::D))
		{
			direction.x += 1.0f;
		}
	
		glm::vec3 translation = GetTransform()->GetLocalFrontDirection() * direction.y;
		translation += GetTransform()->GetLocalRightDirection() * direction.x;
	
		if (glm::length(translation) != 0)
		{
			translation = glm::normalize(translation);
			GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + translation * m_Speed * GetEngine().GetTimeManager().GetDeltaTime());
		}
	}

	Tavern::CameraComponent* GetCamera()
	{
		return m_Camera;
	}

private:
	Tavern::CameraComponent* m_Camera;
	float m_Speed;
	float m_Zoom;
};

using namespace Tavern;

int main()
{
	// Setup Tavern Engine
	Engine& engine = Engine::Get();
	Window* window = engine.GetRenderManager().GetWindow();
	window->GetCursor().SetIsLocked(false);
	window->GetCursor().SetIsVisible(true);

	// TODO: Remove this game code
	EditorCamera* editorCamera = engine.GetScene().CreateEntity<EditorCamera>();
	Light* light = engine.GetScene().CreateEntity<Light>();

	// Setup ImGui context
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	//(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // Enable Multi-Viewports
	//io.IniFilename = "imgui.ini";

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    //ImGuiStyle& style = ImGui::GetStyle();
	//style.WindowRounding = 0.0f;
    //style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	// Setup Platform/Renderer backends
	//GLFWwindow* glfwWindow = window->GetGLFWWindow();
	//ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	//ImGui_ImplOpenGL3_Init("#version 460");

	//Taverner::Editor editor(engine, window, "Unnamed Project", 800, 600);
	//engine.GetUIManager().CreateUIElementOfType<Panel>();
	Panel* editor = engine.GetUIManager().AddPanel(new Panel());
	MenuBar* mainMenuBar = dynamic_cast<MenuBar*>(editor->AddUIElement(new MenuBar()));
	while (engine.IsRunning())
	{
		engine.Update();
		//editor.GetGameFramebuffer().Bind();
		engine.Render();
		//editor.GetGameFramebuffer().Unbind();
	}

	// Cleanup
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	return 0;
}

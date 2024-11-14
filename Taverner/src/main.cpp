#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Renderer/Window.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Resources/MaterialResource.h"
#include "Tavern/Resources/MeshResource.h"
#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Components/LightComponent.h"
#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Events/EventManager.h"
#include "Tavern/Events/KeyEvent.h"
#include "Tavern/Events/MouseEvent.h"

class Cube : public Tavern::Entity
{
public:
	Cube(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Assets/Materials/Cube.material");
		std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Meshes/Cube.obj");
		m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
		m_Mesh->SetMesh(mesh);
	}

	void Update() override
	{
		Tavern::Entity::Update();
	}

	Tavern::MeshComponent* m_Mesh;
};

class Light : public Tavern::Entity
{
public:
	Light(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		m_StartPosition = glm::vec3(0.0f, 1.0f, -3.0f);
		GetTransform()->SetLocalPosition(m_StartPosition);
		GetTransform()->SetLocalScale(glm::vec3(0.25f));

		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Assets/Materials/Light.material");
		std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Meshes/Cube.obj");
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

	Tavern::MeshComponent* m_Mesh;
	Tavern::LightComponent* m_Light;
	glm::vec3 m_StartPosition;
};

class Player : public Tavern::Entity
{
public:
	Player(Tavern::Engine& engine)
		: Tavern::Entity(engine), m_Speed(2.5f), m_LastMousePosition(0.0f),
		  m_CameraSensitivity(0.05f), m_Zoom(45.0f),
		  m_KeyPressed(std::bind(&Player::OnKeyPressed, this, std::placeholders::_1)),
		  m_MouseMoved(std::bind(&Player::OnMouseMoved, this, std::placeholders::_1)),
		  m_MouseScrolled(std::bind(&Player::OnMouseScrolled, this, std::placeholders::_1)),
		  m_MouseButtonPressed(std::bind(&Player::OnMouseButtonPressed, this, std::placeholders::_1))
	{
		m_Camera = CreateComponentOfType<Tavern::CameraComponent>();
		GetEngine().GetRenderManager().SetActiveCamera(m_Camera);

		GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetTransform()->SetLocalEulerRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		GetEngine().GetEventManager().AddListener(Tavern::EventType::KeyPressed, m_KeyPressed);
		GetEngine().GetEventManager().AddListener(Tavern::EventType::MouseMoved, m_MouseMoved);
		GetEngine().GetEventManager().AddListener(Tavern::EventType::MouseScrolled, m_MouseScrolled);
		GetEngine().GetEventManager().AddListener(Tavern::EventType::MouseButtonPressed, m_MouseButtonPressed);
	}

	~Player()
	{
		GetEngine().GetEventManager().RemoveListener(Tavern::EventType::KeyPressed, m_KeyPressed);
		GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseMoved, m_MouseMoved);
		GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseScrolled, m_MouseScrolled);
		GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseButtonPressed, m_MouseButtonPressed);
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

		if (m_Cubes.size() >= 2)
		{
			const glm::vec3& cube1Rotation = m_Cubes[0]->GetTransform()->GetLocalEulerRotation();
			m_Cubes[0]->GetTransform()->SetLocalEulerRotation({ cube1Rotation.x,
																cube1Rotation.y,
																cube1Rotation.z + 90.0f * GetEngine().GetTimeManager().GetDeltaTime() });

			const glm::vec3& cube2Rotation = m_Cubes[1]->GetTransform()->GetLocalEulerRotation();
			m_Cubes[1]->GetTransform()->SetLocalEulerRotation({ cube2Rotation.x + 90.0f * GetEngine().GetTimeManager().GetDeltaTime(),
																cube2Rotation.y,
																cube2Rotation.z });
		}
	}

	void OnKeyPressed(const std::shared_ptr<Tavern::KeyPressedEvent>& event)
	{
		if (event->IsRepeat())
		{
			return;
		}

		switch (event->GetKey())
		{
			case Tavern::Key::Escape:
			{
				GetEngine().GetRenderManager().GetWindow()->GetCursor().SetIsLocked(false);
				GetEngine().GetRenderManager().GetWindow()->GetCursor().SetIsVisible(true);
			}
			default:
			{
				return;
			}
		}
	}

	void OnMouseMoved(const std::shared_ptr<Tavern::MouseMovedEvent>& event)
	{
		glm::vec2 mouseOffset(
			event->GetX() - m_LastMousePosition.x,
			event->GetY() - m_LastMousePosition.y
		);
		mouseOffset *= m_CameraSensitivity;

		m_LastMousePosition.x = event->GetX();
		m_LastMousePosition.y = event->GetY();

		const glm::vec3& rotation = GetTransform()->GetLocalEulerRotation();
		GetTransform()->SetLocalEulerRotation(rotation + glm::vec3(-mouseOffset.y, mouseOffset.x, 0.0f));

		if (rotation.x > 89.0f)
		{
			GetTransform()->SetLocalEulerRotation(glm::vec3(89.0f, rotation.y, rotation.z));
		}
		if (rotation.x < -89.0f)
		{
			GetTransform()->SetLocalEulerRotation(glm::vec3(-89.0f, rotation.y, rotation.z));
		}
	}

	void OnMouseScrolled(const std::shared_ptr<Tavern::MouseScrolledEvent>& event)
	{
		m_Zoom -= event->GetYOffset();
		m_Zoom = std::clamp(m_Zoom, 1.0f, 45.0f);

		m_Camera->SetFOV(m_Zoom);
	}

	void OnMouseButtonPressed(const std::shared_ptr<Tavern::MouseButtonPressedEvent>& event)
	{
		if (m_Cubes.empty())
		{
			return;
		}

		Cube* cube = m_Cubes.back();
		m_Cubes.pop_back();

		TAVERN_INFO("Destroyed Cube Entity ID: {}", cube->GetID());
		GetEngine().GetScene().DestroyEntity(cube);
	}

	Tavern::CameraComponent* m_Camera;
	float m_Speed;
	glm::vec2 m_LastMousePosition;
	float m_CameraSensitivity;
	float m_Zoom;
	Tavern::EventListener<Tavern::KeyPressedEvent> m_KeyPressed;
	Tavern::EventListener<Tavern::MouseMovedEvent> m_MouseMoved;
	Tavern::EventListener<Tavern::MouseScrolledEvent> m_MouseScrolled;
	Tavern::EventListener<Tavern::MouseButtonPressedEvent> m_MouseButtonPressed;
	std::vector<Cube*> m_Cubes;
};

int main()
{
	// Setup Tavern Engine
	Tavern::Engine engine;
	Tavern::Window* window = engine.GetRenderManager().GetWindow();
	window->GetCursor().SetIsLocked(false);
	window->GetCursor().SetIsVisible(true);
	Player* player = engine.GetScene().CreateEntity<Player>();
	Light* light = engine.GetScene().CreateEntity<Light>();
	Cube* cube1 = engine.GetScene().CreateEntity<Cube>();
	cube1->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	// Setup ImGui context
	IMGUI_CHECKVERSION();
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

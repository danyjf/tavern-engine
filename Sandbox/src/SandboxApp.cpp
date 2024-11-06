#include <Tavern.h>
#include <algorithm>
#include <functional>
#include <memory>

#include "Tavern/Components/LightComponent.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Core/Time.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Events/MouseEvent.h"
#include "Tavern/Resources/MaterialResource.h"

class MyEntity : public Tavern::Entity
{
public:
	MyEntity(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		std::shared_ptr<Tavern::ShaderResource> shader = GetEngine().GetResourceManager().LoadShader(
			"C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Shaders/LitShader.vert",
			"C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Shaders/LitShader.frag"
		);
		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("CubeMaterial", shader);
		glm::vec3 color = glm::vec3(1.0f);
		material->SetVec3("albedo", color);
		material->SetTexture("albedoMap", GetEngine().GetResourceManager().LoadTexture("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Assets/Textures/container.jpg"));

		m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
	}

	void Update() override
	{
		Tavern::Entity::Update();
	}

	Tavern::MeshComponent* m_Mesh;
};

class LightEntity : public Tavern::Entity
{
public:
	LightEntity(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		m_StartPosition = glm::vec3(0.0f, 1.0f, -3.0f);
		GetTransform()->SetLocalPosition(m_StartPosition);
		GetTransform()->SetLocalScale(glm::vec3(0.25f));

		std::shared_ptr<Tavern::ShaderResource> shader = GetEngine().GetResourceManager().LoadShader(
			"C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Shaders/UnlitShader.vert",
			"C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Shaders/UnlitShader.frag"
		);
		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("LightMaterial", shader);
		glm::vec3 color = glm::vec3(1.0f);
		material->SetVec3("albedo", color);
		material->SetTexture("albedoMap", GetEngine().GetResourceManager().LoadTexture("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Textures/DefaultWhiteTexture.png"));

		m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);

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

		MyEntity* cube = m_Cubes.back();
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
	std::vector<MyEntity*> m_Cubes;
};

int main()
{
	Tavern::Engine TavernEngine;

	// Create startup game entities
	Player* player = TavernEngine.GetScene().CreateEntity<Player>();

	LightEntity* light = TavernEngine.GetScene().CreateEntity<LightEntity>();

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(3.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	MyEntity* cube1 = TavernEngine.GetScene().CreateEntity<MyEntity>();
	cube1->GetTransform()->SetLocalPosition(cubePositions[0]);
	player->m_Cubes.push_back(cube1);

	MyEntity* cube2 = TavernEngine.GetScene().CreateEntity<MyEntity>(cube1);
	cube2->GetTransform()->SetLocalPosition(cubePositions[1]);
	player->m_Cubes.push_back(cube2);

	MyEntity* cube3 = TavernEngine.GetScene().CreateEntity<MyEntity>(cube2);
	cube3->GetTransform()->SetLocalPosition(cubePositions[2]);
	player->m_Cubes.push_back(cube3);

	for (int i = 3; i < 10; i++)
	{
		MyEntity* cube = TavernEngine.GetScene().CreateEntity<MyEntity>();
		cube->GetTransform()->SetLocalPosition(cubePositions[i]);
		cube->GetTransform()->SetLocalEulerRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
		player->m_Cubes.push_back(cube);
	}

	TavernEngine.Run();

	return 0;
}

#include <Tavern/Core/Log.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Components/CameraComponent.h>
#include <Tavern/Components/MeshComponent.h>

#include "Player.h"
#include "Cube.h"

Player::Player(Tavern::Engine& engine)
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

Player::~Player()
{
	GetEngine().GetEventManager().RemoveListener(Tavern::EventType::KeyPressed, m_KeyPressed);
	GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseMoved, m_MouseMoved);
	GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseScrolled, m_MouseScrolled);
	GetEngine().GetEventManager().RemoveListener(Tavern::EventType::MouseButtonPressed, m_MouseButtonPressed);
}

void Player::Update()
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

void Player::OnKeyPressed(const std::shared_ptr<Tavern::KeyPressedEvent>& event)
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

void Player::OnMouseMoved(const std::shared_ptr<Tavern::MouseMovedEvent>& event)
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

void Player::OnMouseScrolled(const std::shared_ptr<Tavern::MouseScrolledEvent>& event)
{
	m_Zoom -= event->GetYOffset();
	m_Zoom = std::clamp(m_Zoom, 1.0f, 45.0f);

	m_Camera->SetFOV(m_Zoom);
}

void Player::OnMouseButtonPressed(const std::shared_ptr<Tavern::MouseButtonPressedEvent>& event)
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

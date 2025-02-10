#include <Tavern/Core/Log.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Components/CameraComponent.h>
#include <Tavern/Components/MeshComponent.h>

#include "Player.h"
#include "Cube.h"

using namespace Tavern;

Player::Player(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner), m_Speed(2.5f), m_LastMousePosition(0.0f),
	  m_CameraSensitivity(0.05f), m_Zoom(45.0f),
	  m_KeyPressed(std::bind(&Player::OnKeyPressed, this, std::placeholders::_1)),
	  m_MouseMoved(std::bind(&Player::OnMouseMoved, this, std::placeholders::_1)),
	  m_MouseScrolled(std::bind(&Player::OnMouseScrolled, this, std::placeholders::_1)),
	  m_MouseButtonPressed(std::bind(&Player::OnMouseButtonPressed, this, std::placeholders::_1))
{
	m_Camera = GetOwner()->CreateComponentOfType<CameraComponent>();
	GetEngine().GetRenderManager().SetActiveCamera(m_Camera);

	GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(0.0f, -90.0f, 0.0f));

	GetEngine().GetEventManager().AddListener("KeyPressed", m_KeyPressed);
	GetEngine().GetEventManager().AddListener("MouseMoved", m_MouseMoved);
	GetEngine().GetEventManager().AddListener("MouseScrolled", m_MouseScrolled);
	GetEngine().GetEventManager().AddListener("MouseButtonPressed", m_MouseButtonPressed);
}

Player::~Player()
{
	GetEngine().GetEventManager().RemoveListener("KeyPressed", m_KeyPressed);
	GetEngine().GetEventManager().RemoveListener("MouseMoved", m_MouseMoved);
	GetEngine().GetEventManager().RemoveListener("MouseScrolled", m_MouseScrolled);
	GetEngine().GetEventManager().RemoveListener("MouseButtonPressed", m_MouseButtonPressed);
}

void Player::Update()
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

	if (m_Cubes.size() >= 2)
	{
		const glm::vec3& cube1Rotation = m_Cubes[0]->GetOwner()->GetTransform()->GetLocalEulerRotation();
		m_Cubes[0]->GetOwner()->GetTransform()->SetLocalEulerRotation({ cube1Rotation.x,
															cube1Rotation.y,
															cube1Rotation.z + 90.0f * GetEngine().GetTimeManager().GetDeltaTime() });

		const glm::vec3& cube2Rotation = m_Cubes[1]->GetOwner()->GetTransform()->GetLocalEulerRotation();
		m_Cubes[1]->GetOwner()->GetTransform()->SetLocalEulerRotation({ cube2Rotation.x + 90.0f * GetEngine().GetTimeManager().GetDeltaTime(),
															cube2Rotation.y,
															cube2Rotation.z });
	}
}

void Player::OnKeyPressed(const std::shared_ptr<KeyPressedEvent>& event)
{
	if (event->IsRepeat())
	{
		return;
	}

	switch (event->GetKey())
	{
		case Key::Escape:
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

void Player::OnMouseMoved(const std::shared_ptr<MouseMovedEvent>& event)
{
	glm::vec2 mouseOffset(
		event->GetX() - m_LastMousePosition.x,
		event->GetY() - m_LastMousePosition.y
	);
	mouseOffset *= m_CameraSensitivity;

	m_LastMousePosition.x = event->GetX();
	m_LastMousePosition.y = event->GetY();

	const glm::vec3& rotation = GetOwner()->GetTransform()->GetLocalEulerRotation();
	GetOwner()->GetTransform()->SetLocalEulerRotation(rotation + glm::vec3(-mouseOffset.y, mouseOffset.x, 0.0f));

	if (rotation.x > 89.0f)
	{
		GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(89.0f, rotation.y, rotation.z));
	}
	if (rotation.x < -89.0f)
	{
		GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(-89.0f, rotation.y, rotation.z));
	}
}

void Player::OnMouseScrolled(const std::shared_ptr<MouseScrolledEvent>& event)
{
	m_Zoom -= event->GetYOffset();
	m_Zoom = std::clamp(m_Zoom, 1.0f, 45.0f);

	m_Camera->SetFOV(m_Zoom);
}

void Player::OnMouseButtonPressed(const std::shared_ptr<MouseButtonPressedEvent>& event)
{
	if (m_Cubes.empty())
	{
		return;
	}

	Cube* cube = m_Cubes.back();
	m_Cubes.pop_back();

	TAVERN_INFO("Destroyed Cube With Entity ID: {}", cube->GetOwner()->GetID());
	GetEngine().GetScene().DestroyEntity(cube->GetOwner());
}

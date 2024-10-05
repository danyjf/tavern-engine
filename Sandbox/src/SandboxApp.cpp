#include "Tavern/Core/Log.h"
#include "Tavern/Events/EventListener.h"
#include <Tavern.h>
#include <algorithm>
#include <functional>
#include <memory>

class MyEntity : public Tavern::Entity
{
public:
	MyEntity(Tavern::Engine* engine)
		: Tavern::Entity(engine)
	{
		m_Mesh = std::make_unique<Tavern::MeshComponent>(GetEngine(), this);

		Tavern::Texture texture1(Tavern::TextureSettings(), "Assets/Images/container.jpg");
		Tavern::Texture texture2(Tavern::TextureSettings(), "Assets/Images/awesomeface.jpg");

		m_Mesh->AddTexture(texture1);
		m_Mesh->AddTexture(texture2);
	}

	void Update() override
	{
		Tavern::Entity::Update();
	}

	std::unique_ptr<Tavern::MeshComponent> m_Mesh;
};

class Player : public Tavern::Entity
{
public:
	Player(Tavern::Engine* engine)
		: Tavern::Entity(engine), m_Speed(2.5f), m_LastMousePosition(0.0f),
		  m_CameraSensitivity(0.05f), m_Zoom(45.0f)
	{
		m_Camera = std::make_unique<Tavern::CameraComponent>(GetEngine(), this);
		GetEngine()->GetRenderManager().SetActiveCamera(m_Camera.get());

		GetTransformComponent()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetTransformComponent()->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		GetEngine()->GetEventManager().AddListener(Tavern::EventType::KeyPressed, new Tavern::EventListener(std::bind(&Player::OnKeyPressed, this, std::placeholders::_1)));
		GetEngine()->GetEventManager().AddListener(Tavern::EventType::MouseMoved, new Tavern::EventListener(std::bind(&Player::OnMouseMoved, this, std::placeholders::_1)));
		GetEngine()->GetEventManager().AddListener(Tavern::EventType::MouseScrolled, new Tavern::EventListener(std::bind(&Player::OnMouseScrolled, this, std::placeholders::_1)));
	}

	void Update() override
	{
		glm::vec2 direction(0.0f);

		if (GetEngine()->GetInputManager().IsKeyPressed(Tavern::Key::W))
		{
			direction.y += 1.0f;
		}
		if (GetEngine()->GetInputManager().IsKeyPressed(Tavern::Key::S))
		{
			direction.y -= 1.0f;
		}
		if (GetEngine()->GetInputManager().IsKeyPressed(Tavern::Key::A))
		{
			direction.x -= 1.0f;
		}
		if (GetEngine()->GetInputManager().IsKeyPressed(Tavern::Key::D))
		{
			direction.x += 1.0f;
		}

		glm::vec3 translation = GetTransformComponent()->GetFrontDirection() * direction.y;
		translation += GetTransformComponent()->GetRightDirection() * direction.x;

		if (glm::length(translation) != 0)
		{
			translation = glm::normalize(translation);
			GetTransformComponent()->SetPosition(GetTransformComponent()->GetPosition() + translation * m_Speed * Tavern::Time::GetDeltaTime());
		}
	}

	void OnKeyPressed(const std::shared_ptr<Tavern::Event>& event)
	{
		std::shared_ptr<Tavern::KeyPressedEvent> keyPressedEvent = std::dynamic_pointer_cast<Tavern::KeyPressedEvent>(event);

		if (keyPressedEvent->IsRepeat())
		{
			return;
		}

		switch (keyPressedEvent->GetKey())
		{
			case Tavern::Key::Escape:
			{
				GetEngine()->GetRenderManager().GetWindow()->GetCursor().SetIsLocked(false);
				GetEngine()->GetRenderManager().GetWindow()->GetCursor().SetIsVisible(true);
			}
			default:
			{
				return;
			}
		}
	}

	void OnMouseMoved(const std::shared_ptr<Tavern::Event>& event)
	{
		std::shared_ptr<Tavern::MouseMovedEvent> mouseMovedEvent = std::dynamic_pointer_cast<Tavern::MouseMovedEvent>(event);
		glm::vec2 mouseOffset(
			mouseMovedEvent->GetX() - m_LastMousePosition.x,
			mouseMovedEvent->GetY() - m_LastMousePosition.y
		);
		mouseOffset *= m_CameraSensitivity;

		m_LastMousePosition.x = mouseMovedEvent->GetX();
		m_LastMousePosition.y = mouseMovedEvent->GetY();

		const glm::vec3& rotation = GetTransformComponent()->GetRotation();
		GetTransformComponent()->SetRotation(rotation + glm::vec3(-mouseOffset.y, mouseOffset.x, 0.0f));

		if (rotation.x > 89.0f)
		{
			GetTransformComponent()->SetRotation(glm::vec3(89.0f, rotation.y, rotation.z));
		}
		if (rotation.x < -89.0f)
		{
			GetTransformComponent()->SetRotation(glm::vec3(-89.0f, rotation.y, rotation.z));
		}
	}

	void OnMouseScrolled(const std::shared_ptr<Tavern::Event>& event)
	{
		std::shared_ptr<Tavern::MouseScrolledEvent> mouseScrolledEvent = std::dynamic_pointer_cast<Tavern::MouseScrolledEvent>(event);

		m_Zoom -= mouseScrolledEvent->GetYOffset();
		m_Zoom = std::clamp(m_Zoom, 1.0f, 45.0f);

		m_Camera->SetFOV(m_Zoom);
	}

	std::unique_ptr<Tavern::CameraComponent> m_Camera;
	float m_Speed;
	glm::vec2 m_LastMousePosition;
	float m_CameraSensitivity;
	float m_Zoom;
};

int main()
{
	Tavern::Engine TavernEngine;

	// Create startup game entities
	TavernEngine.CreateEntity<Player>();

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.2f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	for (int i = 0; i < 10; i++)
	{
		Tavern::Entity* cube = TavernEngine.CreateEntity<MyEntity>();
		cube->GetTransformComponent()->SetPosition(cubePositions[i]);
		cube->GetTransformComponent()->SetRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
	}

	TavernEngine.Run();

	return 0;
}

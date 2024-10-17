#include "Tavern/Core/Log.h"
#include "Tavern/Events/EventListener.h"
#include "Tavern/Events/MouseEvent.h"
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
		m_Mesh = CreateComponentOfType<Tavern::MeshRenderComponent>();

		// std::shared_ptr<Tavern::TextureResource> texture1 = std::make_shared<Tavern::TextureResource>(GetEngine()->GetResourceManager(), "Assets/Images/container.jpg");
		// std::shared_ptr<Tavern::TextureResource> texture2 = std::make_shared<Tavern::TextureResource>(GetEngine()->GetResourceManager(), "Assets/Images/awesomeface.jpg");

		std::shared_ptr<Tavern::TextureResource> texture1 = GetEngine()->GetResourceManager().LoadTexture("Assets/Images/container.jpg");
		std::shared_ptr<Tavern::TextureResource> texture2 = GetEngine()->GetResourceManager().LoadTexture("Assets/Images/awesomeface.jpg");

		m_Mesh->AddTexture(texture1);
		m_Mesh->AddTexture(texture2);
	}

	void Update() override
	{
		Tavern::Entity::Update();
	}

	Tavern::MeshRenderComponent* m_Mesh;
};

class Player : public Tavern::Entity
{
public:
	Player(Tavern::Engine* engine)
		: Tavern::Entity(engine), m_Speed(2.5f), m_LastMousePosition(0.0f),
		  m_CameraSensitivity(0.05f), m_Zoom(45.0f),
		  m_KeyPressed(std::bind(&Player::OnKeyPressed, this, std::placeholders::_1)),
		  m_MouseMoved(std::bind(&Player::OnMouseMoved, this, std::placeholders::_1)),
		  m_MouseScrolled(std::bind(&Player::OnMouseScrolled, this, std::placeholders::_1)),
		  m_MouseButtonPressed(std::bind(&Player::OnMouseButtonPressed, this, std::placeholders::_1))
	{
		m_Camera = CreateComponentOfType<Tavern::CameraComponent>();
		GetEngine()->GetRenderManager().SetActiveCamera(m_Camera);

		GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetTransform()->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		GetEngine()->GetEventManager().AddListener(Tavern::EventType::KeyPressed, m_KeyPressed);
		GetEngine()->GetEventManager().AddListener(Tavern::EventType::MouseMoved, m_MouseMoved);
		GetEngine()->GetEventManager().AddListener(Tavern::EventType::MouseScrolled, m_MouseScrolled);
		GetEngine()->GetEventManager().AddListener(Tavern::EventType::MouseButtonPressed, m_MouseButtonPressed);
	}

	~Player()
	{
		GetEngine()->GetEventManager().RemoveListener(Tavern::EventType::KeyPressed, m_KeyPressed);
		GetEngine()->GetEventManager().RemoveListener(Tavern::EventType::MouseMoved, m_MouseMoved);
		GetEngine()->GetEventManager().RemoveListener(Tavern::EventType::MouseScrolled, m_MouseScrolled);
		GetEngine()->GetEventManager().RemoveListener(Tavern::EventType::MouseButtonPressed, m_MouseButtonPressed);
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

		glm::vec3 translation = GetTransform()->GetFrontDirection() * direction.y;
		translation += GetTransform()->GetRightDirection() * direction.x;

		if (glm::length(translation) != 0)
		{
			translation = glm::normalize(translation);
			GetTransform()->SetPosition(GetTransform()->GetPosition() + translation * m_Speed * Tavern::Time::GetDeltaTime());
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
				GetEngine()->GetRenderManager().GetWindow()->GetCursor().SetIsLocked(false);
				GetEngine()->GetRenderManager().GetWindow()->GetCursor().SetIsVisible(true);
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

		const glm::vec3& rotation = GetTransform()->GetRotation();
		GetTransform()->SetRotation(rotation + glm::vec3(-mouseOffset.y, mouseOffset.x, 0.0f));

		if (rotation.x > 89.0f)
		{
			GetTransform()->SetRotation(glm::vec3(89.0f, rotation.y, rotation.z));
		}
		if (rotation.x < -89.0f)
		{
			GetTransform()->SetRotation(glm::vec3(-89.0f, rotation.y, rotation.z));
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
		GetEngine()->DestroyEntity(cube);
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
	Player* player = TavernEngine.CreateEntity<Player>();

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
		MyEntity* cube = TavernEngine.CreateEntity<MyEntity>();
		cube->GetTransform()->SetPosition(cubePositions[i]);
		cube->GetTransform()->SetRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
		player->m_Cubes.push_back(cube);
	}

	TavernEngine.Run();

	return 0;
}

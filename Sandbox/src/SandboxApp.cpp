#include "Tavern/Core/Log.h"
#include "Tavern/Events/KeyEvent.h"
#include <Tavern.h>
#include <functional>
#include <memory>

class MyEntity : public Tavern::Entity
{
public:
	MyEntity()
	{
		m_Mesh = std::make_unique<Tavern::MeshComponent>(this);

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
	Player()
	{
		m_Camera = std::make_unique<Tavern::CameraComponent>(this);
		Tavern::RenderManager::Get().SetActiveCamera(m_Camera.get());

		GetTransformComponent()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetTransformComponent()->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));

		Tavern::EventManager::Get().AddListener(Tavern::EventType::KeyPressed, std::bind(&Player::OnKeyPressed, this, std::placeholders::_1));
	}

	void Update() override
	{
	}

	void OnKeyPressed(const std::shared_ptr<Tavern::Event>& event)
	{
		std::shared_ptr<Tavern::KeyPressedEvent> keyPressedEvent = std::dynamic_pointer_cast<Tavern::KeyPressedEvent>(event);

		switch (keyPressedEvent->GetKey())
		{
			case Tavern::Key::W:
			{
				TAVERN_INFO("KeyPressed(W)");
				break;
			}
			case Tavern::Key::A:
			{
				TAVERN_INFO("KeyPressed(A)");
				break;
			}
			case Tavern::Key::S:
			{
				TAVERN_INFO("KeyPressed(S)");
				break;
			}
			case Tavern::Key::D:
			{
				TAVERN_INFO("KeyPressed(D)");
				break;
			}
			case Tavern::Key::UpArrow:
			{
				TAVERN_INFO("KeyPressed(UpArrow)");
				break;
			}
			case Tavern::Key::LeftArrow:
			{
				TAVERN_INFO("KeyPressed(LeftArrow)");
				break;
			}
			case Tavern::Key::DownArrow:
			{
				TAVERN_INFO("KeyPressed(DownArrow)");
				break;
			}
			case Tavern::Key::RightArrow:
			{
				TAVERN_INFO("KeyPressed(RightArrow)");
				break;
			}
		}
	}

	std::unique_ptr<Tavern::CameraComponent> m_Camera;
};

int main()
{
	std::unique_ptr<Tavern::Engine> TavernEngine = std::make_unique<Tavern::Engine>();

	TavernEngine->Init();

	TavernEngine->CreateEntity<Player>();

	// Create startup game entities
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
		Tavern::Entity* cube = TavernEngine->CreateEntity<MyEntity>();
		cube->GetTransformComponent()->SetPosition(cubePositions[i]);
		cube->GetTransformComponent()->SetRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
	}

	TavernEngine->GameLoop();

	TavernEngine->Shutdown();

	return 0;
}

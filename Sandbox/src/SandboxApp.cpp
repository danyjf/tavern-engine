#include <Tavern.h>

class MyEntity : public Tavern::Entity
{
public:
	MyEntity()
	{
		Tavern::TextureSettings textureSettings;
		Tavern::Texture texture1(Tavern::TextureSettings(), "Assets/Images/container.jpg");
		Tavern::Texture texture2(Tavern::TextureSettings(), "Assets/Images/awesomeface.jpg");
		AddTexture(texture1);
		AddTexture(texture2);
	}

	void Update() override
	{
		Tavern::Entity::Update();
	}
};

int main()
{
	Tavern::Engine* TavernEngine = new Tavern::Engine();

	TavernEngine->Init();

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
		cube->m_Transform->SetPosition(cubePositions[i]);
		cube->m_Transform->SetRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
	}

	TavernEngine->GameLoop();

	TavernEngine->Shutdown();

	return 0;
}

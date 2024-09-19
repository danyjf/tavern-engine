#include <Tavern.h>
#include <memory>

class MyEntity : public Tavern::Entity
{
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
	Tavern::Entity* entity = TavernEngine->CreateEntity<MyEntity>();
	Tavern::TextureSettings textureSettings;
	std::shared_ptr<Tavern::Texture> texture1 = std::make_shared<Tavern::Texture>(Tavern::TextureSettings(), "container.jpg");
	std::shared_ptr<Tavern::Texture> texture2 = std::make_shared<Tavern::Texture>(Tavern::TextureSettings(), "awesomeface.jpg");
	entity->AddTexture(texture1);
	entity->AddTexture(texture2);

	TavernEngine->GameLoop();

	TavernEngine->Shutdown();

	return 0;
}

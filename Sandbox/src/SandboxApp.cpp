#include <Tavern.h>

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
	MyEntity entity;
	TavernEngine->AddEntity(entity);

	TavernEngine->GameLoop();

	TavernEngine->Shutdown();

	return 0;
}

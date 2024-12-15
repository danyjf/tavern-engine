#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Cube.h"
#include "Light.h"
#include "Backpack.h"
#include "Player.h"

class Ground : public Tavern::Entity
{
public:
	Ground(Tavern::Engine& engine)
		: Tavern::Entity(engine)
	{
		std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Ground.material");
		std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/ground.obj");
		m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
		m_Mesh->SetMesh(mesh);
		GetTransform()->SetPosition(glm::vec3(0.0f, -8.0f, 0.0f));
	}

private:
	Tavern::MeshComponent* m_Mesh;
};

int main()
{
	//Tavern::Engine& TavernEngine = Tavern::Engine::Get();
	Tavern::Engine TavernEngine;

	// Create startup game entities
	Player* player = TavernEngine.GetScene().CreateEntity<Player>();
	Light* light = TavernEngine.GetScene().CreateEntity<Light>();
	Backpack* backpack = TavernEngine.GetScene().CreateEntity<Backpack>();
	Ground* ground = TavernEngine.GetScene().CreateEntity<Ground>();

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

	Cube* cube1 = TavernEngine.GetScene().CreateEntity<Cube>();
	cube1->GetTransform()->SetLocalPosition(cubePositions[0]);
	player->m_Cubes.push_back(cube1);

	Cube* cube2 = TavernEngine.GetScene().CreateEntity<Cube>(cube1);
	cube2->GetTransform()->SetLocalPosition(cubePositions[1]);
	player->m_Cubes.push_back(cube2);

	Cube* cube3 = TavernEngine.GetScene().CreateEntity<Cube>(cube2);
	cube3->GetTransform()->SetLocalPosition(cubePositions[2]);
	player->m_Cubes.push_back(cube3);

	for (int i = 3; i < 10; i++)
	{
		Cube* cube = TavernEngine.GetScene().CreateEntity<Cube>();
		cube->GetTransform()->SetLocalPosition(cubePositions[i]);
		cube->GetTransform()->SetLocalEulerRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
		player->m_Cubes.push_back(cube);
	}

	while (TavernEngine.IsRunning())
	{
		TavernEngine.Update();
		TavernEngine.GetRenderManager().Render();
		TavernEngine.GetRenderManager().SwapBuffers();
	}

	return 0;
}

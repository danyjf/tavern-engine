#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Cube.h"
#include "Light.h"
#include "Backpack.h"
#include "Ground.h"
#include "Player.h"

int main()
{
	Tavern::Engine engine;

	// Create startup game entities
	Player* player = engine.GetScene().CreateEntity()->CreateComponentOfType<Player>();
	Light* light = engine.GetScene().CreateEntity()->CreateComponentOfType<Light>();
	Backpack* backpack = engine.GetScene().CreateEntity()->CreateComponentOfType<Backpack>();
	Ground* ground = engine.GetScene().CreateEntity()->CreateComponentOfType<Ground>();

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

	Cube* cube1 = engine.GetScene().CreateEntity()->CreateComponentOfType<Cube>();
	cube1->GetOwner()->GetTransform()->SetLocalPosition(cubePositions[0]);
	player->m_Cubes.push_back(cube1);

	Cube* cube2 = engine.GetScene().CreateEntity(cube1->GetOwner())->CreateComponentOfType<Cube>();
	cube2->GetOwner()->GetTransform()->SetLocalPosition(cubePositions[1]);
	player->m_Cubes.push_back(cube2);

	Cube* cube3 = engine.GetScene().CreateEntity(cube2->GetOwner())->CreateComponentOfType<Cube>();
	cube3->GetOwner()->GetTransform()->SetLocalPosition(cubePositions[2]);
	player->m_Cubes.push_back(cube3);

	for (int i = 3; i < 10; i++)
	{
		Cube* cube = engine.GetScene().CreateEntity()->CreateComponentOfType<Cube>();
		cube->GetOwner()->GetTransform()->SetLocalPosition(cubePositions[i]);
		cube->GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(i * 10.0, i * 21.0, i * 13.0));
		player->m_Cubes.push_back(cube);
	}

	while (engine.IsRunning())
	{
		engine.HandleEvents();
		engine.Update();
		engine.Render();
	}

	return 0;
}

#include <Tavern/Core/Engine.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Backpack.h"

Backpack::Backpack(Tavern::Engine& engine)
	: Tavern::Entity(engine)
{
	GetTransform()->SetLocalPosition(glm::vec3(3.0f, 0.0f, 3.0f));

	std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Backpack.material");
	std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/backpack.obj");
	m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
	m_Mesh->SetMesh(mesh);
}

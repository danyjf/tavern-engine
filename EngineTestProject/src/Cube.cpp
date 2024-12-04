#include <Tavern/Core/Engine.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Cube.h"

Cube::Cube(Tavern::Engine& engine)
	: Tavern::Entity(engine)
{
	std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Cube.material");
	std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("BuiltInAssets/Meshes/Cube.obj");
	m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
	m_Mesh->SetMesh(mesh);
}

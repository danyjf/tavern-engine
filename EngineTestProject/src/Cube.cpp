#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Cube.h"

using namespace Tavern;

Cube::Cube(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner)
{
	std::shared_ptr<MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Cube.material");
	std::shared_ptr<MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("BuiltInAssets/Meshes/Cube.obj");
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>(material);
	m_Mesh->SetMesh(mesh);
}

void Cube::Update()
{
}

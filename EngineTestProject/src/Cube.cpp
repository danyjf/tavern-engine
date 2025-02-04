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
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>();
	m_Mesh->SetMaterial(GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Cube.material"));
	m_Mesh->SetMesh(GetEngine().GetResourceManager().LoadMesh("BuiltInAssets/Meshes/Cube.obj"));
}

void Cube::Update()
{
}

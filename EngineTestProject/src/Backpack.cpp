#include <Tavern/Core/Engine.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>

#include "Backpack.h"

using namespace Tavern;

Backpack::Backpack(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner)
{
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>();
	m_Mesh->SetMaterial(GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Backpack.material"));
	m_Mesh->SetMesh(GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/backpack.obj"));

	GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(3.0f, 0.0f, 3.0f));
}

void Backpack::Update()
{
}

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
	GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(3.0f, 0.0f, 3.0f));

	std::shared_ptr<MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Backpack.material");
	std::shared_ptr<MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/backpack.obj");
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>(material);
	m_Mesh->SetMesh(mesh);
}

void Backpack::Update()
{
}

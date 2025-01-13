#include <Tavern/Components/MeshComponent.h>

#include "Ground.h"

using namespace Tavern;

Ground::Ground(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner)
{
	std::shared_ptr<MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Ground.material");
	std::shared_ptr<MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/ground.obj");
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>(material);
	m_Mesh->SetMesh(mesh);
	GetOwner()->GetTransform()->SetPosition(glm::vec3(0.0f, -8.0f, 0.0f));
}

void Ground::Update()
{
}

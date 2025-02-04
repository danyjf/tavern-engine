#include <Tavern/Components/MeshComponent.h>

#include "Ground.h"

using namespace Tavern;

Ground::Ground(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner)
{
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>();
	m_Mesh->SetMaterial(GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Ground.material"));
	m_Mesh->SetMesh(GetEngine().GetResourceManager().LoadMesh("Assets/Meshes/ground.obj"));

	GetOwner()->GetTransform()->SetPosition(glm::vec3(0.0f, -8.0f, 0.0f));
}

void Ground::Update()
{
}

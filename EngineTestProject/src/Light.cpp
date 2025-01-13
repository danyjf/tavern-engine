#include <Tavern/Core/Engine.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/LightComponent.h>

#include "Light.h"

using namespace Tavern;

Light::Light(Engine& engine, Entity* owner)
	: ScriptComponent(engine, owner)
{
	m_StartPosition = glm::vec3(0.0f, 1.0f, -3.0f);
	GetOwner()->GetTransform()->SetLocalPosition(m_StartPosition);
	GetOwner()->GetTransform()->SetLocalScale(glm::vec3(0.25f));

	std::shared_ptr<MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("Assets/Materials/Light.material");
	std::shared_ptr<MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("BuiltInAssets/Meshes/Cube.obj");
	m_Mesh = GetOwner()->CreateComponentOfType<MeshComponent>(material);
	m_Mesh->SetMesh(mesh);

	m_Light = GetOwner()->CreateComponentOfType<LightComponent>();
	m_Light->SetColor(glm::vec3(1.0f));
}

void Light::Update()
{
	GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(
		m_StartPosition.x + sin(2.0f * GetEngine().GetTimeManager().GetElapsedTime()) / 2.0f * 3.0f,
		m_StartPosition.y,
		m_StartPosition.z + cos(GetEngine().GetTimeManager().GetElapsedTime()) * 3.0f
	));
}

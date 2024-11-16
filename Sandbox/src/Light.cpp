#include <Tavern/Core/Engine.h>
#include <Tavern/Resources/MaterialResource.h>
#include <Tavern/Resources/MeshResource.h>
#include <Tavern/Components/MeshComponent.h>
#include <Tavern/Components/LightComponent.h>

#include "Light.h"

Light::Light(Tavern::Engine& engine)
	: Tavern::Entity(engine)
{
	m_StartPosition = glm::vec3(0.0f, 1.0f, -3.0f);
	GetTransform()->SetLocalPosition(m_StartPosition);
	GetTransform()->SetLocalScale(glm::vec3(0.25f));

	std::shared_ptr<Tavern::MaterialResource> material = GetEngine().GetResourceManager().LoadMaterial("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Assets/Materials/Light.material");
	std::shared_ptr<Tavern::MeshResource> mesh = GetEngine().GetResourceManager().LoadMesh("C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/BuiltInAssets/Meshes/Cube.obj");
	m_Mesh = CreateComponentOfType<Tavern::MeshComponent>(material);
	m_Mesh->SetMesh(mesh);

	m_Light = CreateComponentOfType<Tavern::LightComponent>();
	m_Light->SetColor(glm::vec3(1.0f));
}

void Light::Update()
{
	Tavern::Entity::Update();

	GetTransform()->SetLocalPosition(glm::vec3(
		m_StartPosition.x + sin(2.0f * GetEngine().GetTimeManager().GetElapsedTime()) / 2.0f * 3.0f,
		m_StartPosition.y,
		m_StartPosition.z + cos(GetEngine().GetTimeManager().GetElapsedTime()) * 3.0f
	));
}

#include <nlohmann/json.hpp>

#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Resources/MeshResource.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	// TODO: Add a way to get the path to a file instead of putting the absolute path here
	MeshComponent::MeshComponent(Engine& engine, Entity* owner)
		: RenderComponent(engine, owner)
	{
	}

	void MeshComponent::SetMesh(std::shared_ptr<MeshResource> mesh)
	{
		m_Mesh = mesh;
	}

	std::shared_ptr<MeshResource> MeshComponent::GetMesh()
	{
		return m_Mesh;
	}

	void MeshComponent::Render()
	{
		if (!m_IsVisible || !m_Mesh)
		{
			return;
		}

		m_Mesh->Render();
	}

	nlohmann::json MeshComponent::ToJson()
	{
		nlohmann::json renderJson = RenderComponent::ToJson();

		nlohmann::json json;
		json["mesh"] = renderJson;
		json["mesh"]["meshPath"] = m_Mesh ? m_Mesh->GetPath().c_str() : "";
		return json;
	}

	void MeshComponent::FromJson(const nlohmann::json& data)
	{
		SetIsVisible(data["isVisible"]);
		SetMesh(GetEngine().GetResourceManager().LoadMesh(data["meshPath"]));
		SetMaterial(GetEngine().GetResourceManager().LoadMaterial(data["materialPath"]));
	}
}

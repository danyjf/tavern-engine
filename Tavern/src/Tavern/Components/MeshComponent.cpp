#include <nlohmann/json.hpp>

#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Renderer/RenderManager.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Resources/MeshResource.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	// TODO: Add a way to get the path to a file instead of putting the absolute path here
	MeshComponent::MeshComponent(Engine& engine, Entity* owner, std::shared_ptr<MaterialResource> material)
		: RenderComponent(engine, owner, material)
	{
	}

	void MeshComponent::SetMesh(std::shared_ptr<MeshResource> mesh)
	{
		m_Mesh = mesh;
	}

	void MeshComponent::Render()
	{
		if (!m_IsVisible || !m_Mesh)
		{
			return;
		}

		m_Mesh->Render();
	}

	nlohmann::json MeshComponent::Serialize()
	{
		nlohmann::json renderJson = RenderComponent::Serialize();

		nlohmann::json json;
		json["mesh"] = renderJson;
		json["mesh"]["meshPath"] = m_Mesh ? m_Mesh->GetPath().c_str() : "";
		return json;
	}

	void MeshComponent::Deserialize()
	{

	}
}

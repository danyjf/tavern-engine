#include <nlohmann/json.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Resources/MaterialResource.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	RenderComponent::RenderComponent(Engine& engine, Entity* owner)
		: Component(engine, owner)
	{
	}

	RenderComponent::~RenderComponent()
	{
		GetEngine().GetRenderManager().RemoveRenderComponent(this);
	}

	nlohmann::ordered_json RenderComponent::ToJson()
	{
		nlohmann::ordered_json json;
		json["isVisible"] = m_IsVisible;
		json["materialPath"] = m_Material ? m_Material->GetPath() : "";
		return json;
	}

	void RenderComponent::FromJson(const nlohmann::ordered_json& data)
	{

	}

	bool RenderComponent::IsVisible() const
	{
		return m_IsVisible;
	}

	void RenderComponent::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
	}

	std::shared_ptr<MaterialResource> RenderComponent::GetMaterial()
	{
		return m_Material;
	}

	void RenderComponent::SetMaterial(std::shared_ptr<MaterialResource> material)
	{
		m_Material = material;
		GetEngine().GetRenderManager().AddRenderComponent(this);
	}
}

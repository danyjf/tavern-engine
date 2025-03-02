#include <nlohmann/json.hpp>

#include "Tavern/Components/LightComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	LightComponent::LightComponent(Engine& engine, Entity* owner)
		: Component(engine, owner), m_Color(glm::vec3(1.0f))
	{
		GetEngine().GetRenderManager().AddLightComponent(this);
	}

	LightComponent::~LightComponent()
	{
		GetEngine().GetRenderManager().RemoveLightComponent(this);
	}

	nlohmann::ordered_json LightComponent::ToJson()
	{
		nlohmann::ordered_json json;
		json["light"]["color"] = { m_Color.x, m_Color.y, m_Color.z };
		return json;
	}

	void LightComponent::FromJson(const nlohmann::ordered_json& data)
	{
		SetColor(glm::vec3(
			data["color"][0],
			data["color"][1],
			data["color"][2]
		));
	}

	const glm::vec3& LightComponent::GetColor() const
	{
		return m_Color;
	}

	void LightComponent::SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}
}

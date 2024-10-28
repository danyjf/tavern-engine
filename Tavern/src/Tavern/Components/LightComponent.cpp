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

	const glm::vec3& LightComponent::GetColor() const
	{
		return m_Color;
	}

	void LightComponent::SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}
}

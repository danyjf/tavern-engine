#include "Tavern/Components/PointLightComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	PointLightComponent::PointLightComponent(Engine& engine, Entity* owner)
		: RenderComponent(engine, owner),
		  m_Shader(GetEngine().GetResourceManager().LoadShader(
			  "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Shaders/Shader.vert",
			  "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Shaders/Shader.frag"
		  ))
	{
	}

	void PointLightComponent::Render()
	{
		m_Shader->Use();
		m_Shader->SetVec3("lightColor", m_Color);
		glm::vec3 worldLightPos = glm::vec3(GetOwner()->GetParent()->GetTransform()->GetModelMatrix() * glm::vec4(GetOwner()->GetTransform()->GetPosition(), 1.0f));
		m_Shader->SetVec3("lightPos", worldLightPos);
	}

	const glm::vec3& PointLightComponent::GetColor() const
	{
		return m_Color;
	}

	void PointLightComponent::SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}
}

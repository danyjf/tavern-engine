#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	RenderComponent::RenderComponent(Engine& engine, Entity* owner)
		: Component(engine, owner),
		  m_Shader(GetEngine().GetResourceManager().LoadShader(
			  "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Shaders/Shader.vert",
			  "C:/Dev/tavern-engine/bin/Debug-Windows-x64/Sandbox/Shaders/Shader.frag"
		  ))
	{
		GetEngine().GetRenderManager().AddRenderComponent(this);
	}

	RenderComponent::~RenderComponent()
	{
		GetEngine().GetRenderManager().RemoveRenderComponent(this);
	}

	bool RenderComponent::IsVisible() const
	{
		return m_IsVisible;
	}

	void RenderComponent::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
	}
}

#include "Tavern/Components/BaseRenderComponent.h"
#include "Tavern/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	BaseRenderComponent::BaseRenderComponent(Engine* engine, Entity* owner)
		: BaseComponent(engine, owner)
	{
	}

	bool BaseRenderComponent::IsVisible() const
	{
		return m_IsVisible;
	}

	void BaseRenderComponent::SetIsVisible(bool isVisible)
	{
		m_IsVisible = isVisible;
	}
}

#include "Tavern/Components/BaseComponent.h"
#include "Tavern/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	BaseComponent::BaseComponent(Engine* engine, Entity* owner)
		: m_Engine(engine), m_Owner(owner)
	{
	}

	Entity* BaseComponent::GetOwner() const
	{
		return m_Owner;
	}

	Engine* BaseComponent::GetEngine() const
	{
		return m_Engine;
	}
}

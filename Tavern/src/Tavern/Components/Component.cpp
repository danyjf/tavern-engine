#include "Tavern/Components/Component.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	Component::Component(Engine& engine, Entity* owner)
		: m_Engine(engine), m_Owner(owner)
	{
	}

	Entity* Component::GetOwner() const
	{
		return m_Owner;
	}

	Engine& Component::GetEngine() const
	{
		return m_Engine;
	}
}

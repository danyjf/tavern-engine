#include "Tavern/Components/Component.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Component::Component(Entity* owner)
	{
		m_Owner = owner;
	}

	Entity* Component::GetOwner() const
	{
		return m_Owner;
	}
}

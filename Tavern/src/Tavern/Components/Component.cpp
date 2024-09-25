#include "Tavern/Components/Component.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Component::Component(Entity* owner)
	{
		m_Owner = owner;
	}

	Component::~Component()
	{
	}

	Entity* Component::GetOwner() const
	{
		return m_Owner;
	}
}

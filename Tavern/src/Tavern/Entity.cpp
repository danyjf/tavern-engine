#include <memory>

#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Entity::Entity()
	{
		m_Transform = std::make_unique<TransformComponent>(this);
	}

	Entity::~Entity()
	{
	}

	void Entity::Update()
	{
	}

	TransformComponent* Entity::GetTransformComponent() const
	{
		return m_Transform.get();
	}
}

#include <memory>

#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Entity::Entity(Engine* engine)
		: m_Engine(engine)
	{
		m_Transform = std::make_unique<TransformComponent>(m_Engine, this);
	}

	Entity::~Entity()
	{
	}

	void Entity::Update()
	{
	}

	Engine* Entity::GetEngine() const
	{
		return m_Engine;
	}

	TransformComponent* Entity::GetTransformComponent() const
	{
		return m_Transform.get();
	}
}

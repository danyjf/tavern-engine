#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Entity::Entity(Engine* engine)
		: m_Engine(engine)
	{
		m_Transform = CreateComponentOfType<TransformComponent>();
	}

	void Entity::Update()
	{
	}

	Engine* Entity::GetEngine() const
	{
		return m_Engine;
	}

	TransformComponent* Entity::GetTransform() const
	{
		return m_Transform;
	}
}

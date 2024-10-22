#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	Entity::Entity(Engine& engine)
		: m_Engine(engine), m_ID(++s_Counter)
	{
		m_Transform = CreateComponentOfType<TransformComponent>();
	}

	void Entity::Update()
	{
	}

	const unsigned long Entity::GetID() const
	{
		return m_ID;
	}

	Engine& Entity::GetEngine() const
	{
		return m_Engine;
	}

	TransformComponent* Entity::GetTransform() const
	{
		return m_Transform;
	}
}

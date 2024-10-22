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

	Entity::~Entity()
	{
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

	Entity* Entity::GetParent() const
	{
		return m_Parent;
	}

	void Entity::SetParent(Entity* parent)
	{
		// Remove this entity from the list of children of current parent
		if (m_Parent)
		{
			m_Parent->m_Children.erase(m_ID);
		}

		// Add this entity to the list of children of the new parent
		parent->m_Children[m_ID] = this;

		m_Parent = parent;
	}

	std::unordered_map<unsigned long, Entity*>& Entity::GetChildren()
	{
		return m_Children;
	}
}

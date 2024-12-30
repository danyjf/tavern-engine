#include <nlohmann/json.hpp>

#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"

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

	nlohmann::json Entity::Serialize()
	{
		nlohmann::json json;
		json["id"] = m_ID;
		json["parent"] = m_Parent ? m_Parent->GetID() : -1;		// -1 means no parent

		for (Entity* child : m_Children)
		{
			json["children"].push_back(child->GetID());
		}

		json["components"].emplace(m_Transform->Serialize());
		for (const auto& [type, componentVector] : m_Components)
		{
			for (const std::unique_ptr<Component>& component : componentVector)
			{
				json["components"].emplace(component->Serialize());
			}
		}

		return json;
	}
	
	void Entity::Deserialize()
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
		if (m_Parent)
		{
			m_Parent->RemoveChild(this);
		}
		m_Parent = parent;

		m_Parent->AddChild(this);
	}

	std::vector<Entity*>& Entity::GetChildren()
	{
		return m_Children;
	}

	void Entity::RemoveChild(Entity* child)
	{
		m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
	}

	void Entity::AddChild(Entity* child)
	{
		if (std::find(m_Children.begin(), m_Children.end(), child) != m_Children.end())
		{
			TAVERN_ENGINE_ERROR("Tried to add child to entity, but entity is already parent of child");
			return;
		}
		
		m_Children.push_back(child);
	}
}

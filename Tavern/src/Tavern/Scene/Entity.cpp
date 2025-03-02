#include <nlohmann/json.hpp>

#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Components/LightComponent.h"
#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Components/MeshComponent.h"
#include "Tavern/Components/ScriptComponent.h"
#include "Tavern/Scene/Entity.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	Entity::Entity(Engine& engine, unsigned long id, Entity* parent, const std::string& name)
		: m_Engine(engine),
		  m_Name(name),
		  m_ID(id)
	{
		m_Transform = CreateComponentOfType<TransformComponent>();
		if (parent)
		{
			SetParent(parent);
		}
	}

	Entity::~Entity()
	{
	}

	nlohmann::ordered_json Entity::ToJson()
	{
		nlohmann::ordered_json json;
		json["name"] = m_Name;
		for (const std::unique_ptr<Component>& component : m_Components)
		{
			json["components"].update(component->ToJson());
		}
		for (Entity* child : m_Children)
		{
			json["children"].push_back(child->ToJson());
		}

		return json;
	}
	
	void Entity::FromJson(const nlohmann::ordered_json& data)
	{
		m_Name = data["name"];
		for (auto it = data["components"].begin(); it != data["components"].end(); it++)
		{
			const std::string& componentType = it.key();
			const nlohmann::json& componentData = it.value();

			if (componentType == "transform")
			{
				m_Transform->FromJson(componentData);
			}
			else if (componentType == "camera")
			{
				CameraComponent* camera = CreateComponentOfType<CameraComponent>();
				camera->FromJson(componentData);
			}
			else if (componentType == "light")
			{
				LightComponent* light = CreateComponentOfType<LightComponent>();
				light->FromJson(componentData);
			}
			else if (componentType == "mesh")
			{
				// TODO: I think I need a material here
				MeshComponent* mesh = CreateComponentOfType<MeshComponent>();
				mesh->FromJson(componentData);
			}
			else if (componentType == "script")
			{
				ScriptComponent* script = ScriptRegistry::Get().Create(componentData["typeName"], this);
				script->FromJson(componentData);
			}
		}
		
		if (!data.contains("children"))
		{
			return;
		}

		for (const nlohmann::json& childData : data["children"])
		{
			Entity* entity = GetEngine().GetScene().CreateEntity(this);
			entity->FromJson(childData);
		}
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

		m_Transform->SetPosition(m_Transform->GetPosition());
	}

	const std::string& Entity::GetName() const
	{
		return m_Name;
	}

	void Entity::SetName(const std::string& name)
	{
		m_Name = name;
	}

	std::vector<Entity*>& Entity::GetChildren()
	{
		return m_Children;
	}

	std::vector<std::unique_ptr<Component>>& Entity::GetComponents()
	{
		return m_Components;
	}

	void Entity::RemoveChild(Entity* child)
	{
		m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
	}

	void Entity::AddChild(Entity* child)
	{
		m_Children.push_back(child);
	}
}

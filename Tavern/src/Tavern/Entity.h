#pragma once

#include <memory>
#include <vector>
#include <typeindex>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	class Shader;
	class Texture;
	class TransformComponent;
	class BaseComponent;

	class TAVERN_API Entity
	{
	public:
		Entity(Engine* engine);
		virtual ~Entity() = default;
		Entity(Entity& copy) = delete;
		Entity& operator=(const Entity& copy) = delete;

		virtual void Update();

		Engine* GetEngine() const;
		TransformComponent* GetTransformComponent() const;

		template <typename ComponentClass>
		ComponentClass* CreateComponentOfType()
		{
			std::type_index typeIndex(typeid(ComponentClass));

			if (m_Components.contains(typeIndex))
			{
				m_Components[typeIndex].push_back(std::make_unique<ComponentClass>(GetEngine(), this));
			}
			else
			{
				m_Components.emplace(typeIndex, std::vector<std::unique_ptr<BaseComponent>>());
				m_Components[typeIndex].push_back(std::make_unique<ComponentClass>(GetEngine(), this));
			}

			return static_cast<ComponentClass*>(m_Components[typeIndex].back().get());
		}
		template <typename ComponentClass>
		ComponentClass* GetComponentOfType()
		{
			std::type_index typeIndex(typeid(ComponentClass));
			if (m_Components.contains(typeIndex) && !m_Components[typeIndex].empty())
			{
				return static_cast<ComponentClass*>(m_Components[typeIndex][0].get());
			}
			return nullptr;
		}
		template <typename ComponentClass>
		std::vector<ComponentClass*> GetComponentsOfType()
		{
			std::type_index typeIndex(typeid(ComponentClass));
			std::vector<ComponentClass*> components;

			if (!m_Components.contains(typeIndex))
			{
				return components;
			}

			for (std::unique_ptr<BaseComponent>& component : m_Components[typeIndex])
			{
				components.push_back(static_cast<ComponentClass*>(component.get()));
			}

			return components;
		}

	private:
		Engine* m_Engine = nullptr;
		TransformComponent* m_Transform;

		std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseComponent>>> m_Components;
	};
}

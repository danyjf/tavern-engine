#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>

#include "Tavern/Core/Core.h"
#include "Tavern/Scene/Scene.h"

namespace Tavern
{
	class ShaderResource;
	class TextureResource;
	class TransformComponent;
	class Component;
	class Engine;

	class TAVERN_API Entity
	{
	friend class Scene;

	public:
		Entity(Engine& engine);
		virtual ~Entity();

		Entity(Entity& copy) = delete;
		Entity& operator=(const Entity& copy) = delete;

		virtual void Update();

		const unsigned long GetID() const;
		Engine& GetEngine() const;
		TransformComponent* GetTransform() const;
		Entity* GetParent() const;
		void SetParent(Entity* parent);
		std::unordered_map<unsigned long, Entity*>& GetChildren();

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
				m_Components.emplace(typeIndex, std::vector<std::unique_ptr<Component>>());
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

			for (std::unique_ptr<Component>& component : m_Components[typeIndex])
			{
				components.push_back(static_cast<ComponentClass*>(component.get()));
			}

			return components;
		}

	protected:
		std::unordered_map<unsigned long, Entity*> m_Children;
		Entity* m_Parent = nullptr;

	private:
		unsigned long m_ID = 0;
		Engine& m_Engine;
		TransformComponent* m_Transform;
		std::unordered_map<std::type_index, std::vector<std::unique_ptr<Component>>> m_Components;

		static inline unsigned long s_Counter = 0;
	};
}

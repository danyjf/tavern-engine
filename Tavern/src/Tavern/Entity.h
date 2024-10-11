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

		template <typename ComponentClass>
		ComponentClass* CreateComponent()
		{
			ComponentClass* component = new ComponentClass(GetEngine(), this);
			std::type_index typeIndex(typeid(ComponentClass));

			if (m_Components.contains(typeIndex))
			{
				m_Components[typeIndex].emplace_back(std::unique_ptr<ComponentClass>(component));
			}
			else
			{
				m_Components.emplace(typeIndex, std::vector<std::unique_ptr<BaseComponent>>());
				m_Components[typeIndex].emplace_back(std::unique_ptr<ComponentClass>(component));
			}

			return component;
		}

		Engine* GetEngine() const;
		TransformComponent* GetTransformComponent() const;

	private:
		Engine* m_Engine = nullptr;
		TransformComponent* m_Transform;

		std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseComponent>>> m_Components;
	};
}

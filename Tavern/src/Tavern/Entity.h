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

		Engine* GetEngine() const;
		TransformComponent* GetTransformComponent() const;

	private:
		Engine* m_Engine = nullptr;
		TransformComponent* m_Transform;

		std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseComponent>>> m_Components;
	};
}

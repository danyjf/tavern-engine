#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <nlohmann/json.hpp>

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

		nlohmann::json Serialize();
		void Deserialize();

		const unsigned long GetID() const;
		Engine& GetEngine() const;
		TransformComponent* GetTransform() const;

		Entity* GetParent() const;
		void SetParent(Entity* parent);

		std::vector<Entity*>& GetChildren();

		template <typename T, typename... Args>
		T* CreateComponentOfType(Args... args)
		{
			m_Components.push_back(std::make_unique<T>(GetEngine(), this, args...));

			return static_cast<T*>(m_Components.back().get());
		}
		template <typename T>
		T* GetComponentOfType()
		{
			for (std::unique_ptr<Component>& component : m_Components)
			{
				if (typeid(T) == typeid(*component))
				{
					return dynamic_cast<T*>(component.get());
				}
			}
		}

	protected:
		std::vector<Entity*> m_Children;
		Entity* m_Parent = nullptr;

	private:
		unsigned long m_ID = 0;
		Engine& m_Engine;
		TransformComponent* m_Transform;
		std::vector<std::unique_ptr<Component>> m_Components;

		static inline unsigned long s_Counter = 0;

		void RemoveChild(Entity* child);
		void AddChild(Entity* child);
	};
}

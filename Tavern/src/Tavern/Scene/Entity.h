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

		virtual void Update();
		nlohmann::json Serialize();
		void Deserialize();

		const std::string& GetClassName() const;
		void SetClassName(const std::string& className);
		const unsigned long GetID() const;
		Engine& GetEngine() const;
		TransformComponent* GetTransform() const;

		Entity* GetParent() const;
		void SetParent(Entity* parent);

		std::vector<Entity*>& GetChildren();

		template <typename T, typename... Args>
		T* CreateComponentOfType(Args... args)
		{
			std::type_index typeIndex(typeid(T));

			if (m_Components.contains(typeIndex))
			{
				m_Components[typeIndex].push_back(std::make_unique<T>(GetEngine(), this, args...));
			}
			else
			{
				m_Components.emplace(typeIndex, std::vector<std::unique_ptr<Component>>());
				m_Components[typeIndex].push_back(std::make_unique<T>(GetEngine(), this, args...));
			}

			return static_cast<T*>(m_Components[typeIndex].back().get());
		}
		template <typename T>
		T* GetComponentOfType()
		{
			std::type_index typeIndex(typeid(T));
			if (m_Components.contains(typeIndex) && !m_Components[typeIndex].empty())
			{
				return static_cast<T*>(m_Components[typeIndex][0].get());
			}
			return nullptr;
		}
		template <typename T>
		std::vector<T*> GetComponentsOfType()
		{
			std::type_index typeIndex(typeid(T));
			std::vector<T*> components;

			if (!m_Components.contains(typeIndex))
			{
				return components;
			}

			for (std::unique_ptr<Component>& component : m_Components[typeIndex])
			{
				components.push_back(static_cast<T*>(component.get()));
			}

			return components;
		}

	protected:
		std::vector<Entity*> m_Children;
		Entity* m_Parent = nullptr;

	private:
		std::string m_ClassName = "";
		unsigned long m_ID = 0;
		Engine& m_Engine;
		TransformComponent* m_Transform;
		std::unordered_map<std::type_index, std::vector<std::unique_ptr<Component>>> m_Components;

		static inline unsigned long s_Counter = 0;

		void RemoveChild(Entity* child);
		void AddChild(Entity* child);
	};
}

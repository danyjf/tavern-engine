#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <nlohmann/json.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Scene/Scene.h"
#include "Tavern/Components/Component.h"

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
		Entity(Engine& engine, unsigned long id, Entity* parent = nullptr, const std::string& name = "Default");
		virtual ~Entity();

		Entity(Entity& copy) = delete;
		Entity& operator=(const Entity& copy) = delete;

		nlohmann::ordered_json ToJson();
		void FromJson(const nlohmann::ordered_json& data);

		const unsigned long GetID() const;
		Engine& GetEngine() const;
		TransformComponent* GetTransform() const;

		Entity* GetParent() const;
		void SetParent(Entity* parent);

		const std::string& GetName() const;
		void SetName(const std::string& name);

		std::vector<Entity*>& GetChildren();
		std::vector<std::unique_ptr<Component>>& GetComponents();

		template <typename T>
		T* CreateComponentOfType()
		{
			static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

			m_Components.push_back(std::make_unique<T>(GetEngine(), this));

			return static_cast<T*>(m_Components.back().get());
		}
		template <typename T>
		T* GetComponentOfType()
		{
			static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

			for (std::unique_ptr<Component>& componentPtr : m_Components)
			{
				Component* component = componentPtr.get();
				if (component && typeid(T) == typeid(component))
				{
					return static_cast<T*>(component);
				}
			}
			return nullptr;
		}

	protected:
		std::vector<Entity*> m_Children;
		Entity* m_Parent = nullptr;

	private:
		Engine& m_Engine;

		unsigned long m_ID = 0;
		std::string m_Name = "Default";
		TransformComponent* m_Transform;
		std::vector<std::unique_ptr<Component>> m_Components;

		void RemoveChild(Entity* child);
		void AddChild(Entity* child);
	};
}

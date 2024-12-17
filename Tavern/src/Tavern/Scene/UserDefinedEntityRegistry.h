#pragma once

#include <unordered_map>
#include <functional>
#include <string>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Scene;

	class TAVERN_API UserDefinedEntityRegistry
	{
	public:
		static UserDefinedEntityRegistry& Get();

		UserDefinedEntityRegistry(const UserDefinedEntityRegistry& other) = delete;
		UserDefinedEntityRegistry& operator=(const UserDefinedEntityRegistry& other) = delete;

		using CreatorFunction = std::function<Entity*(Entity*)>;
		void Register(const std::string& name, CreatorFunction createEntityFunction);
		void Create(const std::string& name);

		void SetScene(Scene* scene);
		Scene* GetScene() const;

	private:
		Scene* m_Scene = nullptr;
		std::unordered_map<std::string, CreatorFunction> m_Registry = {};

		UserDefinedEntityRegistry();
		~UserDefinedEntityRegistry();
	};
}
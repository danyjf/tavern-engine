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
		static UserDefinedEntityRegistry& Get()
		{
			static UserDefinedEntityRegistry registry;
			return registry;
		}
		UserDefinedEntityRegistry(const UserDefinedEntityRegistry& other) = delete;
		UserDefinedEntityRegistry& operator=(const UserDefinedEntityRegistry& other) = delete;

		using CreatorFunction = std::function<Entity*(Entity*)>;
		void Register(const std::string& name, CreatorFunction createEntityFunction);

		void SetScene(Scene* scene);

	private:
		Scene* m_Scene = nullptr;
		std::unordered_map<std::string, CreatorFunction> m_Registry = {};

		UserDefinedEntityRegistry();
		~UserDefinedEntityRegistry();
	};
}
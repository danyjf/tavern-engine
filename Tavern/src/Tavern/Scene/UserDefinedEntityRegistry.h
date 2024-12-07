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
		UserDefinedEntityRegistry(Scene& scene);
		~UserDefinedEntityRegistry();

		using CreatorFunction = std::function<Entity*(Entity*)>;
		void Register(const std::string& name, CreatorFunction createEntityFunction);

	private:
		Scene& m_Scene;
		std::unordered_map<std::string, CreatorFunction> m_Registry = {};
	};
}
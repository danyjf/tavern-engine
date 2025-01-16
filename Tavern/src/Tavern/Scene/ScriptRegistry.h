#pragma once

#include <unordered_map>
#include <functional>
#include <string>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Scene;
	class ScriptComponent;

	// TODO: Move this to the Editor project
	class TAVERN_API ScriptRegistry
	{
	public:
		static ScriptRegistry& Get();

		ScriptRegistry(const ScriptRegistry& other) = delete;
		ScriptRegistry& operator=(const ScriptRegistry& other) = delete;

		using CreatorFunction = std::function<ScriptComponent*(Entity*)>;
		void Register(const std::string& name, CreatorFunction createEntityFunction);
		ScriptComponent* Create(const std::string& name, Entity* attachToEntity);

		void SetScene(Scene* scene);
		Scene* GetScene() const;

	private:
		Scene* m_Scene = nullptr;
		std::unordered_map<std::string, CreatorFunction> m_Registry = {};

		ScriptRegistry();
		~ScriptRegistry();
	};
}
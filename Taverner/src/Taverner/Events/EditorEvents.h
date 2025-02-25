#pragma once

#include <string>
#include <Tavern/Events/Event.h>

namespace Tavern
{
	class Entity;
}

namespace Taverner
{
	class ProjectConfig;

	class SceneSelectedEvent : public Tavern::Event
	{
	public:
		SceneSelectedEvent(const std::string& scenePath);
		const char* GetName() const override { return "SceneSelectedEvent"; };

		const std::string& GetScenePath() const;

	private:
		std::string m_ScenePath;
	};

	class ProjectLoadedEvent : public Tavern::Event
	{
	public:
		ProjectLoadedEvent(ProjectConfig& projectConfig);
		const char* GetName() const override { return "ProjectLoadedEvent"; };

		const ProjectConfig& GetProjectConfig() const;

	private:
		 ProjectConfig& m_ProjectConfig;
	};

	class EntitySelectedEvent : public Tavern::Event
	{
	public:
		EntitySelectedEvent(Tavern::Entity* entity);
		const char* GetName() const override { return "EntitySelectedEvent"; };

		Tavern::Entity* GetEntity() const;

	private:
		Tavern::Entity* m_Entity;
	};
}

#pragma once

#include <string>
#include <Tavern/Events/Event.h>

namespace Taverner
{
	class ProjectConfig;

	class SceneSelectedEvent : public Tavern::Event
	{
	public:
		SceneSelectedEvent(const std::string& scenePath);
		const char* GetName() const override { return "SceneSelected"; };

		const std::string& GetScenePath() const;

	private:
		std::string m_ScenePath;
	};

	class ProjectLoadedEvent : public Tavern::Event
	{
	public:
		ProjectLoadedEvent(ProjectConfig& projectConfig);
		const char* GetName() const override { return "ProjectLoaded"; };

		const ProjectConfig& GetProjectConfig() const;

	private:
		 ProjectConfig& m_ProjectConfig;
	};
}

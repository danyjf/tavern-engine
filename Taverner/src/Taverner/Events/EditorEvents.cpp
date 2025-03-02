#include "Taverner/Events/EditorEvents.h"
#include "Taverner/Core/ProjectConfig.h"

namespace Taverner
{
	SceneSelectedEvent::SceneSelectedEvent(const std::string& scenePath)
		: m_ScenePath(scenePath)
	{
	}

	const std::string& SceneSelectedEvent::GetScenePath() const
	{
		return m_ScenePath;
	}

	ProjectLoadedEvent::ProjectLoadedEvent(ProjectConfig& projectConfig)
		: m_ProjectConfig(projectConfig)
	{
	}

	const ProjectConfig& ProjectLoadedEvent::GetProjectConfig() const
	{
		return m_ProjectConfig;
	}

	EntitySelectedEvent::EntitySelectedEvent(unsigned long entityID)
		: m_EntityID(entityID)
	{
	}
	
	unsigned long EntitySelectedEvent::GetEntityID() const
	{
		return m_EntityID;
	}
}
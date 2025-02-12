#include "Taverner/Events/EditorEvents.h"

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
}
#pragma once

#include <string>
#include <Tavern/Events/Event.h>

namespace Taverner
{
	class SceneSelectedEvent : public Tavern::Event
	{
	public:
		SceneSelectedEvent(const std::string& scenePath);
		const char* GetName() const override { return "SceneSelected"; };

		const std::string& GetScenePath() const;

	private:
		std::string m_ScenePath;
	};
}

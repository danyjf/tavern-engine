#include <nlohmann/json.hpp>
#include <fstream>

#include "Taverner/ProjectConfig.h"

namespace Taverner
{
	ProjectConfig::ProjectConfig(const std::string& name, const std::string& projectPath, const std::string& gameDLLPath)
		: m_Name(name), m_ProjectPath(projectPath), m_GameDLLPath(gameDLLPath)
	{
	}

	const std::string& ProjectConfig::GetName() const
	{
		return m_Name;
	}

	void ProjectConfig::SetName(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& ProjectConfig::GetProjectPath() const
	{
		return m_ProjectPath;
	}

	void ProjectConfig::SetProjectPath(const std::string& projectPath)
	{
		m_ProjectPath = projectPath;
	}

	const std::string& ProjectConfig::GetGameDLLPath() const
	{
		return m_GameDLLPath;
	}

	void ProjectConfig::SetGameDLLPath(const std::string& gameDLLPath)
	{
		m_GameDLLPath = gameDLLPath;
	}

	void ProjectConfig::Save(const std::string& path)
	{
		nlohmann::json projectConfigJson = {
			{		 "name",		m_Name },
			{ "projectPath", m_ProjectPath },
			{ "gameDLLPath", m_GameDLLPath }
		};

		std::ofstream projectConfigFile(
			path,
			std::ofstream::out | std::ofstream::trunc
		);
		projectConfigFile << projectConfigJson;
		projectConfigFile.close();
	}

	void ProjectConfig::Load(const std::string& path)
	{
		std::ifstream f(path);
		nlohmann::json data = nlohmann::json::parse(f);
		m_Name = data["name"];
		m_ProjectPath = data["projectPath"];
		m_GameDLLPath = data["gameDLLPath"];
	}
}

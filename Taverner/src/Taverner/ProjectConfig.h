#pragma once

#include <string>

namespace Taverner
{
	class ProjectConfig
	{
	public:
		ProjectConfig() = default;
		ProjectConfig(const std::string& name, const std::string& projectPath, const std::string& gameDLLPath);

		const std::string& GetName() const;
		void SetName(const std::string& name);
		const std::string& GetProjectPath() const;
		void SetProjectPath(const std::string& projectPath);
		const std::string& GetGameDLLPath() const;
		void SetGameDLLPath(const std::string& gameDLLPath);

		nlohmann::json ToJson();
		void FromJson(const nlohmann::json& data);

		void Save(const std::string& path);
		void Load(const std::string& path);

	private:
		std::string m_Name = "";
		std::string m_ProjectPath = "";
		std::string m_GameDLLPath = "";
	};
}

#pragma once

#include <nlohmann/json.hpp>

#include <Tavern/Core/Engine.h>

#include "Taverner/ProjectConfig.h"
#include "Taverner/EditorCamera.h"
#include "Taverner/FileSystemWindow.h"
#include "Taverner/GameWindow.h"

namespace Taverner
{
	class Editor
	{
	public:
		Editor(Tavern::Engine& engine);
		~Editor();
		
		void Render();

		void LoadScene(const std::string& scenePath);

		enum EditorState
		{
			Editing,
			Playing,
			Paused
		};
		EditorState GetEditorState();
		EditorCamera& GetEditorCamera();
		GameWindow& GetGameWindow();
		const std::string& GetCurrentScenePath() const;

	private:
		Tavern::Engine& m_Engine;
		Tavern::Window* m_Window;

		EditorState m_EditorState = EditorState::Editing;
		bool m_ProjectLoaded = false;
		ProjectConfig m_ProjectConfig;
		std::string m_EditorPath;
		std::string m_CurrentScenePath;

		GameWindow m_GameWindow;
		EditorCamera m_EditorCamera;
		FileSystemWindow m_FileSystemWindow;

		void CreateNewProject();
		void OpenProject();
		void NewScene();
		void BuildDLL(const std::string& path);
		void LoadDLL(const std::string& dllPath);
	};
}

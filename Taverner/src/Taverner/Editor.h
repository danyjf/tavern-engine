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

		enum EditorState
		{
			Editing,
			Playing,
			Paused
		};
		EditorState GetEditorState();
		EditorCamera& GetEditorCamera();
		GameWindow& GetGameWindow();

	private:
		Tavern::Engine& m_Engine;
		Tavern::Window* m_Window;

		EditorCamera m_EditorCamera;
		EditorState m_EditorState = EditorState::Editing;
		bool m_ProjectLoaded = false;
		ProjectConfig m_ProjectConfig;
		std::string m_EditorPath;

		FileSystemWindow m_FileSystemWindow;
		GameWindow m_GameWindow;

		void CreateNewProject();
		void OpenProject();
		void BuildGameProject(const std::string& path);
		void LoadGame(const std::string& dllPath);
	};
}

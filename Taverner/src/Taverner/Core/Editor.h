#pragma once

#include <nlohmann/json.hpp>

#include <Tavern/Core/Engine.h>
#include <Tavern/Events/EventListener.h>

#include "Taverner/Core/ProjectConfig.h"
#include "Taverner/Core/EditorCamera.h"
#include "Taverner/Windows/FileSystemWindow.h"
#include "Taverner/Windows/GameWindow.h"
#include "Taverner/Windows/SceneWindow.h"
#include "Taverner/Windows/InspectorWindow.h"

namespace Taverner
{
	class SceneSelectedEvent;

	// TODO:
	// - Add scene elements to scene hierarchy display
	// - Display entity components on inspector
	// - Update entity position when changing transform component on inspector
	// - Fix creation of new projects
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
		const std::string& GetCurrentScenePath() const;

	private:
		Tavern::Engine& m_Engine;
		Tavern::Window* m_Window;

		EventListener<SceneSelectedEvent> m_SceneSelectedListener;

		ProjectConfig m_ProjectConfig;
		EditorState m_EditorState = EditorState::Editing;
		bool m_ProjectLoaded = false;
		std::string m_EditorPath;
		std::string m_CurrentScenePath;

		GameWindow m_GameWindow;
		FileSystemWindow m_FileSystemWindow;
		SceneWindow m_SceneWindow;
		InspectorWindow m_InspectorWindow;

		EditorCamera m_EditorCamera;

		void CreateNewProject();
		void OpenProject(const std::string& path);
		void NewScene();
		void LoadScene(const std::string& path);
		void BuildDLL(const std::string& path);
		void LoadDLL(const std::string& dllPath);

		void OnSceneSelected(const std::shared_ptr<SceneSelectedEvent>& event);
	};
}

#pragma once

#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Entity.h>
#include <Tavern/Components/ScriptComponent.h>
#include <Tavern/Components/CameraComponent.h>

using namespace Tavern;

namespace Taverner
{
	class GameWindow;

	class EditorCameraScript : public ScriptComponent
	{
	public:
		EditorCameraScript(Engine& engine, Entity* owner);

		void Update() override;

		CameraComponent* GetCamera();

	private:
		CameraComponent* m_Camera;
		float m_Speed;
		float m_Zoom;
	};

	class EditorCamera
	{
	public:
		EditorCamera(Engine& engine, GameWindow& gameWindow);

		void AddToScene();
		void Reset();

	private:
		Engine& m_Engine;
		GameWindow& m_GameWindow;

		glm::vec3 m_LastPosition = glm::vec3(0.0f);
		glm::vec3 m_LastRotation = glm::vec3(0.0f);
	};
}

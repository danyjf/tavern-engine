#include <imgui.h>

#include "Taverner/Core/EditorCamera.h"
#include "Taverner/Windows/GameWindow.h"

namespace Taverner
{
	EditorCameraScript::EditorCameraScript(Engine& engine, Entity* owner)
		: ScriptComponent(engine, owner),
		  m_Camera(GetOwner()->GetComponentOfType<CameraComponent>()),
		  m_Speed(2.5f),
		  m_Zoom(45.0f)
	{
		GetOwner()->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		GetOwner()->GetTransform()->SetLocalEulerRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}

	void EditorCameraScript::Update()
	{
		glm::vec2 direction(0.0f);

		if (GetEngine().GetInputManager().IsKeyPressed(Key::W))
		{
			direction.y += 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::S))
		{
			direction.y -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::A))
		{
			direction.x -= 1.0f;
		}
		if (GetEngine().GetInputManager().IsKeyPressed(Key::D))
		{
			direction.x += 1.0f;
		}

		glm::vec3 translation = GetOwner()->GetTransform()->GetLocalFrontDirection() * direction.y;
		translation += GetOwner()->GetTransform()->GetLocalRightDirection() * direction.x;

		if (glm::length(translation) != 0)
		{
			translation = glm::normalize(translation);
			GetOwner()->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetLocalPosition() + translation * m_Speed * GetEngine().GetTimeManager().GetDeltaTime());
		}
	}

	CameraComponent* EditorCameraScript::GetCamera()
	{
		return m_Camera;
	}

	EditorCamera::EditorCamera(Engine& engine, GameWindow& gameWindow)
		: m_Engine(engine), m_GameWindow(gameWindow)
	{
	}

	void EditorCamera::AddToScene()
	{
		Entity* editorCamera = m_Engine.GetScene().CreateEntity(nullptr, "EditorCamera");
		CameraComponent* cameraComponent = editorCamera->CreateComponentOfType<CameraComponent>();
		editorCamera->CreateComponentOfType<EditorCameraScript>();

		ImVec2 viewportSize = m_GameWindow.GetViewportSize();
		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f)
		{
			cameraComponent->SetViewportSize(viewportSize.x, viewportSize.y);
		}

		m_Engine.GetRenderManager().SetActiveCamera(cameraComponent);
	}

	void EditorCamera::Reset()
	{
		
	}
}
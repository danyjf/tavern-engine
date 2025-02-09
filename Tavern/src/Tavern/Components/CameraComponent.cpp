#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Core/Log.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	CameraComponent::CameraComponent(Engine& engine, Entity* owner)
		: Component(engine, owner),
		  m_OwnerTransform(GetOwner()->GetTransform())
	{
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	CameraComponent::~CameraComponent()
	{
		if (GetEngine().GetRenderManager().GetActiveCamera() == this)
		{
			GetEngine().GetRenderManager().SetActiveCamera(nullptr);
		}
	}

	nlohmann::json CameraComponent::ToJson()
	{
		nlohmann::json json;
		json["camera"]["fov"] = m_FOV;
		json["camera"]["viewportWidth"] = m_ViewportWidth;
		json["camera"]["viewportHeight"] = m_ViewportHeight;
		json["camera"]["nearClipPlane"] = m_NearClipPlane;
		json["camera"]["farClipPlane"] = m_FarClipPlane;
		return json;
	}

	void CameraComponent::FromJson(const nlohmann::json& data)
	{
		SetFOV(data["fov"]);
		SetViewportSize(data["viewportWidth"], data["viewportHeight"]);
		SetNearClipPlane(data["nearClipPlane"]);
		SetFarClipPlane(data["farClipPlane"]);
	}

	void CameraComponent::SetFOV(float FOV)
	{
		m_FOV = FOV;
		ComputeProjectionMatrix();
	}

	const float CameraComponent::GetFOV() const
	{
		return m_FOV;
	}
	
	void CameraComponent::SetViewportSize(float width, float height)
	{
		if (width <= 0.0f || height <= 0.0f)
		{
			TAVERN_ENGINE_ERROR("Tried to set camera widht or height to a value <= 0");
			return;
		}
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		ComputeProjectionMatrix();
	}

	const glm::vec2 CameraComponent::GetViewportSize() const
	{
		return glm::vec2(m_ViewportWidth, m_ViewportHeight);
	}

	void CameraComponent::SetNearClipPlane(float nearClipPlane)
	{
		m_NearClipPlane = nearClipPlane;
		ComputeProjectionMatrix();
	}

	const float CameraComponent::GetNearClipPlane() const
	{
		return m_NearClipPlane;
	}

	void CameraComponent::SetFarClipPlane(float farClipPlane)
	{
		m_FarClipPlane = farClipPlane;
		ComputeProjectionMatrix();
	}

	const float CameraComponent::GetFarClipPlane() const
	{
		return m_FarClipPlane;
	}

	const glm::mat4& CameraComponent::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	const glm::mat4& CameraComponent::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4 CameraComponent::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::ComputeViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_OwnerTransform->GetLocalPosition(), m_OwnerTransform->GetLocalPosition() + m_OwnerTransform->GetFrontDirection(), m_OwnerTransform->GetUpDirection());
	}

	void CameraComponent::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(
			glm::radians(m_FOV),
			m_ViewportWidth / m_ViewportHeight,
			m_NearClipPlane,
			m_FarClipPlane
		);
	}
}

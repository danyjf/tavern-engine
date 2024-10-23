#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class ShaderResource;

	class TAVERN_API PointLightComponent : public RenderComponent
	{
	public:
		PointLightComponent(Engine& engine, Entity* owner);
		virtual ~PointLightComponent() = default;

		void Render() override;

		const glm::vec3& GetColor() const;
		void SetColor(const glm::vec3& color);

	private:
		std::shared_ptr<ShaderResource> m_Shader = nullptr;
		glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
	};
}

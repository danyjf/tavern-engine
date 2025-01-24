#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Components/Component.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API LightComponent : public Component
	{
	public:
		LightComponent(Engine& engine, Entity* owner);
		virtual ~LightComponent() override;

		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& data) override;

		const glm::vec3& GetColor() const;
		void SetColor(const glm::vec3& color);

	private:
		glm::vec3 m_Color = glm::vec3(1.0f);
	};
}

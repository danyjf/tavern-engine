#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Core/Core.h"
#include "Tavern/Resources/MeshResource.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API MeshComponent : public RenderComponent
	{
	public:
		MeshComponent(Engine& engine, Entity* owner, std::shared_ptr<MaterialResource> material);
		virtual ~MeshComponent() = default;

		void SetMesh(std::shared_ptr<MeshResource> mesh);
		void Render() override;
		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& data) override;

	private:
		std::shared_ptr<MeshResource> m_Mesh = nullptr;
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}

#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class ShaderResource;
	class Engine;

	class TAVERN_API MeshComponent : public RenderComponent
	{
	public:
		MeshComponent(Engine& engine, Entity* owner);
		virtual ~MeshComponent() = default;

		void Render() override;
		void AddTexture(const std::shared_ptr<TextureResource>& texture);
		const glm::vec3& GetColor() const;
		void SetColor(const glm::vec3& color);
		const bool IsUnlit() const;
		void SetUnlit(bool isUnlit);

	private:
		std::shared_ptr<ShaderResource> m_Shader = nullptr;
		std::vector<std::shared_ptr<TextureResource>> m_Textures = {};
		glm::vec3 m_Color = glm::vec3(0.0f);
		bool m_IsUnlit = false;
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}

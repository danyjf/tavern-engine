#pragma once

#include <memory>
#include <vector>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Resources/TextureResource.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class ShaderResource;
	class Engine;

	class TAVERN_API MeshRenderComponent : public RenderComponent
	{
	public:
		MeshRenderComponent(Engine& engine, Entity* owner);
		virtual ~MeshRenderComponent() = default;

		void Render() override;
		void AddTexture(const std::shared_ptr<TextureResource>& texture);

	private:
		std::shared_ptr<ShaderResource> m_Shader = nullptr;
		std::vector<std::shared_ptr<TextureResource>> m_Textures = {};
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}

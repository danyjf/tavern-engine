#pragma once

#include <vector>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Renderer/Texture.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Shader;
	class Engine;

	class TAVERN_API MeshRenderComponent : public RenderComponent
	{
	public:
		MeshRenderComponent(Engine* engine, Entity* owner);
		virtual ~MeshRenderComponent() = default;

		void Render() override;
		void AddTexture(const Texture& texture);

	private:
		Shader* m_Shader = nullptr;
		std::vector<Texture> m_Textures = {};
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}

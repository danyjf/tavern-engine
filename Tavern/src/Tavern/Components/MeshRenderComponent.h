#pragma once

#include <vector>

#include "Tavern/Components/BaseRenderComponent.h"
#include "Tavern/Renderer/Texture.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Shader;
	class Engine;

	class TAVERN_API MeshRenderComponent : public BaseRenderComponent
	{
	public:
		MeshRenderComponent(Engine* engine, Entity* owner);

		void Render() override;
		void AddTexture(const Texture& texture);

	private:
		Shader* m_Shader;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

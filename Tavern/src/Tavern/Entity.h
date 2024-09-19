#pragma once

#include <vector>
#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Shader.h"
#include "Tavern/Renderer/Texture.h"

namespace Tavern
{
	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

		void AddTexture(std::shared_ptr<Texture>& texture);

	private:
		Shader* m_Shader;
		std::vector<std::shared_ptr<Texture> > m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

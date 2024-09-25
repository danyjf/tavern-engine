#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Shader;
	class Texture;
	class TransformComponent;

	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

		TransformComponent* GetTransformComponent() const;
		void AddTexture(const Texture& texture);

		// TODO: Remove this
		bool m_Render;

	private:
		std::unique_ptr<TransformComponent> m_Transform;
		Shader* m_Shader;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

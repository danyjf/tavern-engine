#pragma once

#include <vector>

#include "Tavern/Components/Component.h"
#include "Tavern/Renderer/Texture.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Shader;
	class Engine;

	class TAVERN_API MeshComponent : public Component
	{
	public:
		MeshComponent() = default;
		MeshComponent(Engine* engine, Entity* owner);
		~MeshComponent() = default;

		void Render();
		void AddTexture(const Texture& texture);

		bool IsVisible() const;
		void SetIsVisible(bool isVisible);

	private:
		bool m_IsVisible;
		Shader* m_Shader;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

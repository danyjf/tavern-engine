#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Tavern/Components/RenderComponent.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class ShaderResource;
	class Engine;

	class TAVERN_API MeshComponent : public RenderComponent
	{
	public:
		MeshComponent(Engine& engine, Entity* owner, std::shared_ptr<MaterialResource> material);
		virtual ~MeshComponent() = default;

		void Render() override;

	private:
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}

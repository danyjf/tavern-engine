#pragma once

#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class TAVERN_API MeshResource : public Resource
	{
	public:
		MeshResource(ResourceManager& resourceManager, const std::string& path, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		virtual ~MeshResource() override = default;

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

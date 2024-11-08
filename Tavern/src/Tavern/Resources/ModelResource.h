#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	class MeshResource;

	class TAVERN_API ModelResource : public Resource
	{
	public:
		ModelResource(ResourceManager& resourceManager, const std::string& path);
		virtual ~ModelResource() override = default;

	private:
		std::vector<std::shared_ptr<MeshResource>> m_Meshes;

		void ProcessNode(aiNode* node, const aiScene* scene);
		std::shared_ptr<MeshResource> ProcessMesh(aiMesh* mesh, int id, const aiScene* scene);
	};
}

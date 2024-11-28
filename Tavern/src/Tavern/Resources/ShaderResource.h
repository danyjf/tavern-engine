#pragma once

#include <string>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	class TAVERN_API ShaderResource : public Resource
	{
	public:
		ShaderResource(ResourceManager& resourceManager, const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~ShaderResource() = default;

		void Bind();

		const unsigned int GetID() const { return ID; }
		const std::unordered_set<std::string>& GetBuiltInUniforms() const { return m_BuiltInUniforms; }
		const std::unordered_map<std::string, std::pair<GLenum, int>>& GetMaterialUniforms() const { return m_MaterialUniforms; }
		const int GetMaterialUniformBufferSize() const { return m_MaterialUniformBufferSize; }
		const std::vector<std::string>& GetSamplers() const { return m_Samplers; }

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetMat4(const std::string& name, const glm::mat4& value) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;

	private:
		// The program id
		unsigned int ID = 0;
		std::unordered_set<std::string> m_BuiltInUniforms;
		std::unordered_map<std::string, std::pair<GLenum, int>> m_MaterialUniforms;
		int m_MaterialUniformBufferSize = 0;

		// The index corresponds to the texture unit
		std::vector<std::string> m_Samplers;

		int GetOpenGLTypeSize(GLenum type);
	};
}

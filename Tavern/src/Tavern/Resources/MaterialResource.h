#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/ShaderResource.h"

namespace Tavern
{
	class TAVERN_API MaterialResource : public Resource
	{
	public:
		MaterialResource(ResourceManager& resourceManager, const std::string& path, std::shared_ptr<ShaderResource> shader);
		virtual ~MaterialResource() override = default;

		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetMat4(const std::string& name, glm::mat4& value);
		void SetVec3(const std::string& name, glm::vec3& value);

		std::shared_ptr<ShaderResource> GetShader() { return m_Shader; }

		void Use();

	private:
		std::shared_ptr<ShaderResource> m_Shader;
		std::vector<unsigned char> m_UniformBuffer;

		void SetUniformInBuffer(const std::string& name, unsigned char* valueBegin, int size);
	};
}

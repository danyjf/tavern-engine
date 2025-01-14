#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"
#include "Tavern/Resources/ShaderResource.h"

namespace Tavern
{
	class TextureResource;

	class TAVERN_API MaterialResource : public Resource
	{
	public:
		MaterialResource(ResourceManager& resourceManager, const std::string& path);
		virtual ~MaterialResource() override = default;

		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetMat4(const std::string& name, glm::mat4& value);
		void SetVec3(const std::string& name, glm::vec3& value);
		void SetTexture(const std::string& name, const std::shared_ptr<TextureResource>& value);

		const std::string GetName() const;
		std::shared_ptr<ShaderResource> GetShader();
		const std::shared_ptr<TextureResource> GetTexture(const std::string& name);

		void Bind();

	private:
		std::string m_Name;
		std::shared_ptr<ShaderResource> m_Shader = nullptr;
		std::vector<unsigned char> m_UniformBuffer;
		std::unordered_map<std::string, std::shared_ptr<TextureResource>> m_Textures = {};

		void SetUniformInBuffer(const std::string& name, unsigned char* valueBegin, int size);
	};
}

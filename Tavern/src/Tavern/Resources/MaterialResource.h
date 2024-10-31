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
		MaterialResource(ResourceManager& resourceManager, const std::string& path, std::shared_ptr<ShaderResource> shader);
		virtual ~MaterialResource() override = default;

		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetMat4(const std::string& name, glm::mat4& value);
		void SetVec3(const std::string& name, glm::vec3& value);

		void AddTexture(const std::shared_ptr<TextureResource>& texture);

		std::shared_ptr<ShaderResource> GetShader();
		const glm::vec3& GetColor() const;
		void SetColor(const glm::vec3& color);
		const bool IsUnlit() const;
		void SetUnlit(bool isUnlit);
		const std::vector<std::shared_ptr<TextureResource>>& GetTextures();

		void Use();

	private:
		std::shared_ptr<ShaderResource> m_Shader;
		std::vector<unsigned char> m_UniformBuffer;
		std::vector<std::shared_ptr<TextureResource>> m_Textures = {};

		glm::vec3 m_Color = glm::vec3(1.0f);
		int m_IsUnlit = false;

		void SetUniformInBuffer(const std::string& name, unsigned char* valueBegin, int size);
	};
}

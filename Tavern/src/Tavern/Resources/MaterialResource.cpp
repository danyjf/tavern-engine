#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Resources/MaterialResource.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	MaterialResource::MaterialResource(ResourceManager& resourceManager, const std::string& path, std::shared_ptr<ShaderResource> shader)
		: Resource(resourceManager, path), m_Shader(shader)
	{
		m_UniformBuffer.resize(m_Shader->GetMaterialUniformBufferSize());

		for (auto& pair : m_Shader->GetMaterialUniforms())
		{
			TAVERN_ENGINE_TRACE("Material Uniform Name: {}", pair.first);
		}
	}

	void MaterialResource::SetBool(const std::string& name, bool value)
	{
		unsigned char* valueBegin = reinterpret_cast<unsigned char*>(&value);
		SetUniformInBuffer(name, valueBegin, sizeof(bool));
	}

	void MaterialResource::SetInt(const std::string& name, int value)
	{
		unsigned char* valueBegin = reinterpret_cast<unsigned char*>(&value);
		SetUniformInBuffer(name, valueBegin, sizeof(int));
	}

	void MaterialResource::SetFloat(const std::string& name, float value)
	{
		unsigned char* valueBegin = reinterpret_cast<unsigned char*>(&value);
		SetUniformInBuffer(name, valueBegin, sizeof(float));
	}

	void MaterialResource::SetMat4(const std::string& name, glm::mat4& value)
	{
		float* matrixArray = glm::value_ptr(value);
		unsigned char* valueBegin = reinterpret_cast<unsigned char*>(matrixArray);
		SetUniformInBuffer(name, valueBegin, sizeof(glm::mat4));
	}

	void MaterialResource::SetVec3(const std::string& name, glm::vec3& value)
	{
		float* vecArray = glm::value_ptr(value);
		unsigned char* valueBegin = reinterpret_cast<unsigned char*>(vecArray);
		SetUniformInBuffer(name, valueBegin, sizeof(glm::vec3));
	}

	void MaterialResource::SetUniformInBuffer(const std::string& name, unsigned char* valueBegin, int valueSize)
	{
		if (m_Shader->GetMaterialUniforms().contains(name))
		{
			int bufferOffset = m_Shader->GetMaterialUniforms().at(name).second;

			std::copy(valueBegin, valueBegin + valueSize, m_UniformBuffer.begin() + bufferOffset);
		}
		else
		{
			TAVERN_ENGINE_WARN("Tried to set the uniform {0}, but {0} does not exist in the shader", name);
		}
	}

	void MaterialResource::AddTexture(const std::shared_ptr<TextureResource>& texture)
	{
		if (m_Textures.size() == 16)
		{
			TAVERN_ENGINE_ERROR("Failed to add texture. Maximum of 16 textures reached.");
			return;
		}

		m_Textures.push_back(texture);
	}

	std::shared_ptr<ShaderResource> MaterialResource::GetShader()
	{
		return m_Shader;
	}

	const std::vector<std::shared_ptr<TextureResource>>& MaterialResource::GetTextures()
	{
		return m_Textures;
	}

	void MaterialResource::Use()
	{
		for (auto pair : m_Shader->GetMaterialUniforms())
		{
			GLenum type = pair.second.first;
			const std::string& name = pair.first;
			int byteOffset = pair.second.second;
			switch (type)
			{
				case GL_FLOAT:
				{
					float value;
					std::memcpy(&value, m_UniformBuffer.data() + byteOffset, sizeof(float));
					m_Shader->SetFloat(name, value);
					break;
				}
				case GL_FLOAT_VEC2:
				{
					break;
				}
				case GL_FLOAT_VEC3:
				{
					glm::vec3 value;
					std::memcpy(glm::value_ptr(value), m_UniformBuffer.data() + byteOffset, sizeof(glm::vec3));
					m_Shader->SetVec3(name, value);
					break;
				}
				case GL_FLOAT_VEC4:
				{
					break;
				}
				case GL_INT:
				{
					int value;
					std::memcpy(&value, m_UniformBuffer.data() + byteOffset, sizeof(int));
					m_Shader->SetInt(name, value);
					break;
				}
				case GL_INT_VEC2:
				{
					break;
				}
				case GL_INT_VEC3:
				{
					break;
				}
				case GL_INT_VEC4:
				{
					break;
				}
				case GL_BOOL:
				{
					bool value;
					std::memcpy(&value, m_UniformBuffer.data() + byteOffset, sizeof(bool));
					m_Shader->SetBool(name, value);
					break;
				}
				case GL_BOOL_VEC2:
				{
					break;
				}
				case GL_BOOL_VEC3:
				{
					break;
				}
				case GL_BOOL_VEC4:
				{
					break;
				}
				case GL_FLOAT_MAT2:
				{
					break;
				}
				case GL_FLOAT_MAT3:
				{
					break;
				}
				case GL_FLOAT_MAT4:
				{
					glm::mat4 value;
					std::memcpy(glm::value_ptr(value), m_UniformBuffer.data() + byteOffset, sizeof(glm::mat4));
					m_Shader->SetMat4(name, value);
					break;
				}
				case GL_FLOAT_MAT2x3:
				{
					break;
				}
				case GL_FLOAT_MAT2x4:
				{
					break;
				}
				case GL_FLOAT_MAT3x2:
				{
					break;
				}
				case GL_FLOAT_MAT3x4:
				{
					break;
				}
				case GL_FLOAT_MAT4x2:
				{
					break;
				}
				case GL_FLOAT_MAT4x3:
				{
					break;
				}
			}
		}
	}
}

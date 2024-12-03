#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

#include "Tavern/Resources/MaterialResource.h"
#include "Tavern/Resources/ResourceManager.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	MaterialResource::MaterialResource(ResourceManager& resourceManager, const std::string& path)
		: Resource(resourceManager, path)
	{
		std::ifstream file(path);
		if (file.fail())
		{
			TAVERN_ENGINE_ERROR("Failed to read file at {}. File does not exist", path);
		}
		nlohmann::json data = nlohmann::json::parse(file);

		m_Name = data["name"];
		m_Shader = resourceManager.LoadShader(data["vertexShader"], data["fragmentShader"]);
		m_UniformBuffer.resize(m_Shader->GetMaterialUniformBufferSize());

		for (const auto& pair : m_Shader->GetMaterialUniforms())
		{
			const std::string& uniform = pair.first;
			std::string type = data["properties"][uniform]["type"];

			if (type == "vec3")
			{
				std::array<float, 3> arr = data["properties"][uniform]["value"];
				glm::vec3 value(arr[0], arr[1], arr[2]);
				SetVec3(uniform, value);
			}
			else if (type == "float")
			{
				float value = data["properties"][uniform]["value"];
				SetFloat(uniform, value);
			}
		}

		for (const std::string& sampler : m_Shader->GetSamplers())
		{
			std::shared_ptr<TextureResource> texture = resourceManager.LoadTexture(data["textures"][sampler]);
			SetTexture(sampler, texture);
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

	void MaterialResource::SetTexture(const std::string& name, const std::shared_ptr<TextureResource>& value)
	{
		const std::vector<std::string>& samplers = m_Shader->GetSamplers();
		if (std::find(samplers.begin(), samplers.end(), name) == samplers.end())
		{
			TAVERN_ENGINE_WARN("Tried to set the texture sampler {0}, but {0} does not exist in the shader", name);
			return;
		}

		m_Textures.emplace(name, value);
	}

	const std::string MaterialResource::GetName() const
	{
		return m_Name;
	}

	std::shared_ptr<ShaderResource> MaterialResource::GetShader()
	{
		return m_Shader;
	}

	const std::shared_ptr<TextureResource> MaterialResource::GetTexture(const std::string& name)
	{
		if (!m_Textures.contains(name))
		{
			TAVERN_ENGINE_WARN("Tried to get the texture sampler {0}, but {0} does not exist in the shader", name);
			return nullptr;
		}
		return m_Textures.at(name);
	}

	// TODO: Should look into uniform buffers in OpenGL, I think that there is a way to send
	// all uniforms at once into the GPU using a uniform buffer.
	// Currently, I am sending one at a time, if I want to improve this, I could create my
	// own uniform type classes like, IntShaderUniform, FloatShaderUniform, etc..., and then
	// have a function like, SendToGPU(Shader* shader, uniform char* buffer), implemented in
	// each uniform class to easily send them to the GPU.
	void MaterialResource::Bind()
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

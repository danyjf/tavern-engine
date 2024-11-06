#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Resources/ShaderResource.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	ShaderResource::ShaderResource(ResourceManager& resourceManager, const std::string& vertexPath, const std::string& fragmentPath)
		: Resource(resourceManager, vertexPath + ":" + fragmentPath)
	{
		// Read the shader code from the file paths
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream;
			std::stringstream fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			TAVERN_ENGINE_ERROR("Shader file not successfully read");
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Compile shaders
		unsigned int vertex;
		unsigned int fragment;
		int success;
		char infoLog[512];

		// Vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Vertex Shader Compilation Failed: {0}", infoLog);
		};

		// Fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Fragment Shader Compilation Failed: {0}", infoLog);
		};

		// Shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			TAVERN_ENGINE_ERROR("Program Linking Failed: {0}", infoLog);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		// Get data about uniform variables
		Use();
		int count;
		glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);

		int uniformBufferOffset = 0;
		for (int i = 0; i < count; i++)
		{
			char name[256];
			int length;
			int nElements;
			GLenum type;
			glGetActiveUniform(ID, (GLuint)i, sizeof(name), &length, &nElements, &type, name);
			std::string stripedName(name, length);

			// Catch the built in uniforms
			if (stripedName == "model"
				|| stripedName == "view"
				|| stripedName == "projection"
				|| stripedName == "lightColor"
				|| stripedName == "lightPos"
				|| stripedName == "viewPos")
			{
				m_BuiltInUniforms.insert(stripedName);
				continue;
			}

			// Catch the sampler uniforms
			if (type == GL_SAMPLER_2D)
			{
				m_Samplers.emplace_back(stripedName);
				int samplerIndex = m_Samplers.size() - 1;
				SetInt(m_Samplers.back(), samplerIndex);
				continue;
			}

			// Catch the material uniforms
			m_MaterialUniforms.emplace(stripedName, std::pair<GLenum, int>{ type, uniformBufferOffset });
			uniformBufferOffset += GetOpenGLTypeSize(type) * nElements;
		}
		m_MaterialUniformBufferSize = uniformBufferOffset;
	}

	void ShaderResource::Use()
	{
		glUseProgram(ID);
	}

	void ShaderResource::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void ShaderResource::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void ShaderResource::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void ShaderResource::SetMat4(const std::string& name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderResource::SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
	}

	int ShaderResource::GetOpenGLTypeSize(GLenum type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return sizeof(GLfloat); // Single float
			case GL_FLOAT_VEC2:
				return 2 * sizeof(GLfloat); // vec2 (2 floats)
			case GL_FLOAT_VEC3:
				return 3 * sizeof(GLfloat); // vec3 (3 floats)
			case GL_FLOAT_VEC4:
				return 4 * sizeof(GLfloat); // vec4 (4 floats)
			case GL_INT:
				return sizeof(GLint); // Single int
			case GL_INT_VEC2:
				return 2 * sizeof(GLint); // ivec2 (2 ints)
			case GL_INT_VEC3:
				return 3 * sizeof(GLint); // ivec3 (3 ints)
			case GL_INT_VEC4:
				return 4 * sizeof(GLint); // ivec4 (4 ints)
			case GL_BOOL:
				return sizeof(GLboolean); // Single boolean
			case GL_BOOL_VEC2:
				return 2 * sizeof(GLboolean); // bvec2 (2 booleans)
			case GL_BOOL_VEC3:
				return 3 * sizeof(GLboolean); // bvec3 (3 booleans)
			case GL_BOOL_VEC4:
				return 4 * sizeof(GLboolean); // bvec4 (4 booleans)
			case GL_FLOAT_MAT2:
				return 4 * sizeof(GLfloat); // mat2 (2x2 floats)
			case GL_FLOAT_MAT3:
				return 9 * sizeof(GLfloat); // mat3 (3x3 floats)
			case GL_FLOAT_MAT4:
				return 16 * sizeof(GLfloat); // mat4 (4x4 floats)
			case GL_FLOAT_MAT2x3:
				return 6 * sizeof(GLfloat); // mat2x3 (2x3 floats)
			case GL_FLOAT_MAT2x4:
				return 8 * sizeof(GLfloat); // mat2x4 (2x4 floats)
			case GL_FLOAT_MAT3x2:
				return 6 * sizeof(GLfloat); // mat3x2 (3x2 floats)
			case GL_FLOAT_MAT3x4:
				return 12 * sizeof(GLfloat); // mat3x4 (3x4 floats)
			case GL_FLOAT_MAT4x2:
				return 8 * sizeof(GLfloat); // mat4x2 (4x2 floats)
			case GL_FLOAT_MAT4x3:
				return 12 * sizeof(GLfloat); // mat4x3 (4x3 floats)
			case GL_SAMPLER_2D:
				return sizeof(GLint); // sampler (typically an int for binding purposes)
			case GL_SAMPLER_CUBE:
				return sizeof(GLint); // sampler (typically an int for binding purposes)
			// Add cases for other types as needed
			default:
				printf("Unknown OpenGL type: 0x%x\n", type);
				return 0; // Unknown type
		}
	}
}

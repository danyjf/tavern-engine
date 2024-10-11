#pragma once

#include <string>
#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		void Use();

		const unsigned int GetID() const { return ID; };

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetMat4(const std::string& name, const glm::mat4& value) const;

	private:
		// The program id
		unsigned int ID = 0;
	};
}

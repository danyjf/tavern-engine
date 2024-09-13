#pragma once

#include <string>

namespace Tavern
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		void Use();

		const unsigned int GetID() const { return ID; };

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;

	private:
		// The program id
		unsigned int ID;
	};
}

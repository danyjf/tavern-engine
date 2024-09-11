#pragma once

#include "Tavern/Core.h"

namespace Tavern
{
	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

	private:
		unsigned int m_ShaderProgram;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

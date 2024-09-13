#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Shader.h"

namespace Tavern
{
	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

	private:
		Shader* m_Shader;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}

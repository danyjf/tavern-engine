#include "RenderManager.h"

namespace Tavern
{
	RenderManager& RenderManager::Get()
	{
		static RenderManager s_RenderManager;
		return s_RenderManager;
	}

	void RenderManager::Init()
	{
		m_Shader = std::make_shared<Shader>(
			"./Shaders/Shader.vert",
			"./Shaders/Shader.frag");
	}

	void RenderManager::Shutdown()
	{
	}
}

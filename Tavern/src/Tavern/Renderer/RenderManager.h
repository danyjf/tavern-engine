#pragma once

#include <memory>

#include "Shader.h"

namespace Tavern
{
	class RenderManager
	{
	public:
		RenderManager(RenderManager& copy) = delete;
		void operator=(const RenderManager& copy) = delete;

		static RenderManager& Get();

		const std::shared_ptr<Shader> GetShader() const { return m_Shader; }

		void Init();
		void Shutdown();

	private:
		RenderManager() {};
		~RenderManager() {};

		std::shared_ptr<Shader> m_Shader;
	};
}

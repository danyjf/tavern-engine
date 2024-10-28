#pragma once

#include "Tavern/Components/Component.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Engine;
	class Entity;
	class ShaderResource;

	class TAVERN_API RenderComponent : public Component
	{
	public:
		RenderComponent(Engine& engine, Entity* owner);
		virtual ~RenderComponent() override;

		virtual void Render() = 0;

		bool IsVisible() const;
		void SetIsVisible(bool isVisible);
		std::shared_ptr<ShaderResource> GetShader() { return m_Shader; }

	protected:
		bool m_IsVisible = true;
		std::shared_ptr<ShaderResource> m_Shader = nullptr;
	};
}

#pragma once

#include "Tavern/Components/Component.h"
#include "Tavern/Core/Core.h"
#include <memory>

namespace Tavern
{
	class Engine;
	class Entity;
	class MaterialResource;

	class TAVERN_API RenderComponent : public Component
	{
	public:
		RenderComponent(Engine& engine, Entity* owner);
		virtual ~RenderComponent() override;

		virtual void Render() = 0;
		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& data) override;

		bool IsVisible() const;
		void SetIsVisible(bool isVisible);
		std::shared_ptr<MaterialResource> GetMaterial();
		void SetMaterial(std::shared_ptr<MaterialResource> material);

	protected:
		bool m_IsVisible = true;
		std::shared_ptr<MaterialResource> m_Material = nullptr;
	};
}

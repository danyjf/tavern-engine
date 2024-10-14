#pragma once

#include "Tavern/Components/Component.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Engine;
	class Entity;

	class TAVERN_API RenderComponent : public Component
	{
	public:
		RenderComponent(Engine* engine, Entity* owner);
		virtual ~RenderComponent() override;

		virtual void Render() = 0;

		bool IsVisible() const;
		void SetIsVisible(bool isVisible);

	protected:
		bool m_IsVisible = true;
	};
}

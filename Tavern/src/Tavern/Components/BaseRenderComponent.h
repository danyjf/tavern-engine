#pragma once

#include "Tavern/Components/BaseComponent.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Engine;
	class Entity;

	class TAVERN_API BaseRenderComponent : public BaseComponent
	{
	public:
		BaseRenderComponent(Engine* engine, Entity* owner);
		virtual ~BaseRenderComponent() override;

		virtual void Render() = 0;

		bool IsVisible() const;
		void SetIsVisible(bool isVisible);

	protected:
		bool m_IsVisible = true;
	};
}

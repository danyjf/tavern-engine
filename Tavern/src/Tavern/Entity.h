#pragma once

#include <memory>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Shader;
	class Texture;
	class TransformComponent;

	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

		TransformComponent* GetTransformComponent() const;

	private:
		std::unique_ptr<TransformComponent> m_Transform;
	};
}

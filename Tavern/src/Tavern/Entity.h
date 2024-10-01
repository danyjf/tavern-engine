#pragma once

#include <memory>

#include "Tavern/Core/Core.h"
#include "Tavern/Core/Engine.h"

namespace Tavern
{
	class Shader;
	class Texture;
	class TransformComponent;

	class TAVERN_API Entity
	{
	public:
		Entity(Engine* engine);
		virtual ~Entity();

		virtual void Update();

		Engine* GetEngine() const;
		TransformComponent* GetTransformComponent() const;

	private:
		Engine* m_Engine;
		std::unique_ptr<TransformComponent> m_Transform;
	};
}

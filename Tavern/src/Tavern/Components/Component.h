#pragma once

namespace Tavern
{
	class Entity;

	class Component
	{
	public:
		Component() = default;
		Component(Entity* owner);
		~Component() = default;

		Entity* GetOwner() const;

	private:
		Entity* m_Owner;
	};
}

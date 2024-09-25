#pragma once

namespace Tavern
{
	class Entity;

	class Component
	{
	public:
		Component() = default;
		Component(Entity* owner);
		~Component();

		Entity* GetOwner() const;

	private:
		Entity* m_Owner;
	};
}

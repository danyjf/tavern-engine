#pragma once

namespace Tavern
{
	class Entity;

	class Component
	{
	public:
		Component();
		~Component();

		Entity* GetOwner() const;

	private:
		Entity* m_Owner;
	};
}

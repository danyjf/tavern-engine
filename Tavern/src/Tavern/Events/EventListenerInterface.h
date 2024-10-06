#pragma once

#include <memory>

namespace Tavern
{
	class Event;

	class EventListenerInterface
	{
	public:
		virtual void Call(const std::shared_ptr<Event>&) = 0;
		virtual const int GetID() const = 0;
	};
}

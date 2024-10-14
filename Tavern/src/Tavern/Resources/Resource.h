#pragma once

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Resource
	{
	public:
		Resource(const std::string& path);

	private:
		std::string m_Path = "";
	};
}

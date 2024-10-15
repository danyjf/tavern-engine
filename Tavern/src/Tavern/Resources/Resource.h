#pragma once

#include <string>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class ResourceManager;

	class TAVERN_API Resource
	{
	public:
		Resource(ResourceManager& resourceManager, const std::string& path);
		virtual ~Resource();

	private:
		ResourceManager& m_ResourceManager;
		std::string m_Path = "";
	};
}

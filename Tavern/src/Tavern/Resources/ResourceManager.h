#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/Resources/Resource.h"

namespace Tavern
{
	class TAVERN_API ResourceManager
	{
	public:
		std::shared_ptr<Resource> Load(const std::string& path);

	private:
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;
	};
}

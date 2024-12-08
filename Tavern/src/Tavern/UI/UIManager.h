#pragma once

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"
#include "Tavern/UI/Panel.h"

namespace Tavern
{
	class RenderManager;

	class TAVERN_API UIManager
	{
	public:
		UIManager(RenderManager& renderManager);
		~UIManager();
		UIManager(UIManager& copy) = delete;
		UIManager& operator=(const UIManager& copy) = delete;

		void Render();
		std::vector<std::unique_ptr<Panel>>& GetPanels();
		Panel* AddPanel(Panel* panel);

	private:
		RenderManager& m_RenderManager;
		std::vector<std::unique_ptr<Panel>> m_Panels;
	};
}

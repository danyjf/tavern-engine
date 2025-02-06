#include <imgui.h>

#include <Tavern/Core/Engine.h>

#include "Taverner/Editor.h"
#include "Taverner/GameWindow.h"

namespace Taverner
{
	GameWindow::GameWindow(Tavern::Engine& engine)
		: m_Engine(engine)
	{
	}

	void GameWindow::Render()
	{
		if (ImGui::Begin("Game", nullptr, ImGuiWindowFlags_None))
		{
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			const FramebufferSettings& settings = m_GameFramebuffer.GetFramebufferSettings();
			if (viewportPanelSize.x > 0.0f && viewportPanelSize.y > 0.0f &&
				(viewportPanelSize.x != settings.Width || viewportPanelSize.y != settings.Height))
			{
				m_GameFramebuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
				m_Engine.GetRenderManager().GetActiveCamera()->SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
			}

			unsigned int textureID = m_GameFramebuffer.GetColorTextures()[0];
			ImGui::Image(textureID, viewportPanelSize);
		}
		ImGui::End();
	}

	Tavern::Framebuffer& GameWindow::GetGameFramebuffer()
	{
		return m_GameFramebuffer;
	}
}
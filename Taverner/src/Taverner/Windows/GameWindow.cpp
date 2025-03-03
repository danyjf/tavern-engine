#include <imgui.h>

#include <Tavern/Core/Engine.h>

#include "Taverner/Core/Editor.h"
#include "Taverner/Windows/GameWindow.h"

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
			m_ViewportSize = ImGui::GetContentRegionAvail();

			const FramebufferSettings& settings = m_GameFramebuffer.GetFramebufferSettings();
			if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
				(m_ViewportSize.x != settings.Width || m_ViewportSize.y != settings.Height))
			{
				m_GameFramebuffer.Resize(m_ViewportSize.x, m_ViewportSize.y);
				m_Engine.GetRenderManager().GetActiveCamera()->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			}

			unsigned int textureID = m_GameFramebuffer.GetColorTextures()[0];
			ImGui::Image(textureID, m_ViewportSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		}
		ImGui::End();
	}

	Tavern::Framebuffer& GameWindow::GetGameFramebuffer()
	{
		return m_GameFramebuffer;
	}

	const ImVec2 GameWindow::GetViewportSize() const
	{
		return m_ViewportSize;
	}
}
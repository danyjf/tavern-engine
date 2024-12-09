#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/Image.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	Image::Image(ImTextureID textureID, ImVec2 size)
		: m_TextureID(textureID), m_Size(size)
	{
	}

	void Image::Render()
	{
		ImGui::Image(m_TextureID, m_Size);
	}

	void Image::SetTextureID(ImTextureID textureID)
	{
		m_TextureID = textureID;
	}

	void Image::SetSize(ImVec2 size)
	{
		m_Size = size;
	}
}

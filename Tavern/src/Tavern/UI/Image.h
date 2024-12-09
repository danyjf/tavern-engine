#pragma once

#include <imgui.h>
#include <string>

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	class TAVERN_API Image : public UIElement
	{
	public:
		Image(ImTextureID textureID, ImVec2 size);
		Image(Image& copy) = delete;
		Image& operator=(const Image& copy) = delete;

		void Render() override;
		void SetTextureID(ImTextureID textureID);
		void SetSize(ImVec2 size);

	private:
		ImTextureID m_TextureID;
		ImVec2 m_Size;
	};
}

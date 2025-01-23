#pragma once

#include <imgui.h>
#include <ImGuiFileDialog.h>

#include "Tavern/Core/Core.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	class TAVERN_API FileDialog : public UIElement
	{
	public:
		FileDialog(const std::string& name, const std::string& fileExtensions, const IGFD::FileDialogConfig config);
		FileDialog(FileDialog& copy) = delete;
		FileDialog& operator=(const FileDialog& copy) = delete;

		using OkPressedFunction = std::function<void()>;
		void AddOnOkListener(OkPressedFunction okPressedFunction);

		void Open();
		std::string GetFilePath();

		void Render() override;

	private:
		ImGuiFileDialog m_ImGuiFileDialog;
		std::string m_Name;
		std::string m_FileExtensions;	// string containing comma separated file extensions (ex. ".cpp,.h,.hpp")
		IGFD::FileDialogConfig m_Config;
		std::vector<OkPressedFunction> m_OkPressedListeners;
	};
}

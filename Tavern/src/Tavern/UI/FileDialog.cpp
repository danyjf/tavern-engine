#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Tavern/UI/FileDialog.h"
#include "Tavern/UI/UIElement.h"

namespace Tavern::UI
{
	FileDialog::FileDialog(const std::string& name, const std::string& fileExtensions, const IGFD::FileDialogConfig config)
		: m_Name(name), m_FileExtensions(fileExtensions), m_Config(config)
	{
	}

	void FileDialog::Render()
	{
		if (m_ImGuiFileDialog.Display(m_Name + "Key"))
		{			
			if (m_ImGuiFileDialog.IsOk()) {
				for (OkPressedFunction& listener : m_OkPressedListeners)
				{
					listener();
				}
			}
			
			m_ImGuiFileDialog.Close();
		}
	}

	void FileDialog::Open()
	{
		m_ImGuiFileDialog.OpenDialog(m_Name + "Key", m_Name, m_FileExtensions.c_str(), m_Config);
	}

	std::string FileDialog::GetFilePath()
	{
		return m_ImGuiFileDialog.GetFilePathName();
	}

	void FileDialog::AddOnOkListener(OkPressedFunction okPressedFunction)
	{
		m_OkPressedListeners.push_back(okPressedFunction);
	}
}

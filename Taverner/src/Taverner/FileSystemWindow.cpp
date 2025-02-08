#include <filesystem>
#include <imgui.h>

#include <Tavern/Core/Log.h>
#include <Tavern/Core/Engine.h>
#include <Tavern/Scene/Scene.h>

#include "Taverner/Editor.h"
#include "Taverner/FileSystemWindow.h"

namespace Taverner
{
	FileSystemWindow::FileSystemWindow(Tavern::Engine& engine, Editor& editor)
		: m_Engine(engine), m_Editor(editor)
	{
	}

	void FileSystemWindow::LoadFileStructure(const std::string& path)
	{
		m_ContentPath = path;

		m_Root = std::make_unique<FileSystemNode>(*this, m_ContentPath, true);
		LoadDir(m_Root.get(), path);
	}

	void FileSystemWindow::LoadDir(FileSystemNode* node, const std::filesystem::path& path)
	{
		for (const std::filesystem::directory_entry& dirEntry 
			: std::filesystem::directory_iterator(path))
		{
			if (dirEntry.is_directory())
			{
				node->AddChild(std::make_unique<FileSystemNode>(*this, dirEntry.path(), true));
				LoadDir(node->GetChildren().back().get(), dirEntry.path());
			}
			else
			{
				node->AddChild(std::make_unique<FileSystemNode>(*this, dirEntry.path(), false));
			}
		}
	}

	void FileSystemWindow::Render()
	{
		if (ImGui::Begin("File System", nullptr, ImGuiWindowFlags_HorizontalScrollbar))
		{
			if (!m_ContentPath.empty())
			{
				m_Root->Render();
			}
		}
		ImGui::End();
	}

	void FileSystemWindow::OpenFile(const std::filesystem::path& filePath)
	{
		std::string fileExtension = filePath.filename().extension().string();

		if (fileExtension == ".scene" && m_Editor.GetCurrentScenePath() != filePath.string())
		{
			m_Editor.LoadScene(filePath.string());
		}
	}

	FileSystemNode::FileSystemNode(FileSystemWindow& fileSystemWindow, const std::filesystem::path& path, bool isDirectory)
		: m_FileSystemWindow(fileSystemWindow), m_Path(path), m_IsDirectory(isDirectory)
	{
	}

	void FileSystemNode::Render()
	{
		if (IsDirectory())
		{
			if (ImGui::TreeNode(GetName().c_str()))
			{
				for (const std::unique_ptr<FileSystemNode>& child : GetChildren())
				{
					child->Render();
				}
				ImGui::TreePop();
			}
		}
		else
		{
			ImGui::TreeNodeEx(GetName().c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				m_FileSystemWindow.OpenFile(m_Path);
			}
		}
	}

	const std::string FileSystemNode::GetName() const
	{
		return m_Path.filename().string();
	}

	bool FileSystemNode::IsDirectory() const
	{
		return m_IsDirectory;
	}

	const std::vector<std::unique_ptr<FileSystemNode>>& FileSystemNode::GetChildren() const
	{
		return m_Children;
	}

	void FileSystemNode::AddChild(std::unique_ptr<FileSystemNode> node)
	{
		m_Children.push_back(std::move(node));
	}
}
#include <filesystem>
#include <imgui.h>

#include "Taverner/FileSystemWindow.h"

namespace Taverner
{
	void FileSystemWindow::LoadFileStructure(const std::string& path)
	{
		m_ContentPath = path;

		m_Root = make_unique<FileSystemNode>(m_ContentPath.filename().string(), true);
		LoadDir(m_Root.get(), path);
	}

	void FileSystemWindow::LoadDir(FileSystemNode* node, const std::filesystem::path& path)
	{
		for (const std::filesystem::directory_entry& dirEntry 
			: std::filesystem::directory_iterator(path))
		{
			if (dirEntry.is_directory())
			{
				node->AddChild(make_unique<FileSystemNode>(dirEntry.path().filename().string(), true));
				LoadDir(node->GetChildren().back().get(), dirEntry.path());
			}
			else
			{
				node->AddChild(make_unique<FileSystemNode>(dirEntry.path().filename().string(), false));
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

	FileSystemNode::FileSystemNode(const std::string& name, bool isDirectory)
		: m_Name(name), m_IsDirectory(isDirectory)
	{
	}

	void FileSystemNode::Render() const
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
			}
		}
	}

	const std::string& FileSystemNode::GetName() const
	{
		return m_Name;
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
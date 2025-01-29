#pragma once

namespace Taverner
{
	class FileSystemNode
	{
	public:
		FileSystemNode(const std::string& name, bool isDirectory);

		virtual void Render() const;
		const std::string& GetName() const;
		bool IsDirectory() const;
		const std::vector<std::unique_ptr<FileSystemNode>>& GetChildren() const;
		void AddChild(std::unique_ptr<FileSystemNode> node);

	private:
		std::string m_Name;
		std::vector<std::unique_ptr<FileSystemNode>> m_Children;
		bool m_IsDirectory;
	};

	class FileSystemWindow
	{
	public:
		void Render();
		void LoadFileStructure(const std::string& path);

	private:
		std::filesystem::path m_ContentPath;
		std::unique_ptr<FileSystemNode> m_Root;

		void LoadDir(FileSystemNode* node, const std::filesystem::path& path);
	};
}
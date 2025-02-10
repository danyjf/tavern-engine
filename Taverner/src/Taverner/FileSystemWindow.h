#pragma once

#include <Tavern/Events/Event.h>

namespace Taverner
{
	class FileSystemWindow;
	class Editor;

	class SceneSelectedEvent : public Tavern::Event
	{
	public:
		SceneSelectedEvent(const std::string& scenePath);
		const char* GetName() const override { return "SceneSelected"; };

		const std::string& GetScenePath() const;

	private:
		std::string m_ScenePath;
	};

	class FileSystemNode
	{
	public:
		FileSystemNode(FileSystemWindow& fileSystemWindow, const std::filesystem::path& path, bool isDirectory);

		virtual void Render();
		const std::string GetName() const;
		bool IsDirectory() const;
		const std::vector<std::unique_ptr<FileSystemNode>>& GetChildren() const;
		void AddChild(std::unique_ptr<FileSystemNode> node);

	private:
		FileSystemWindow& m_FileSystemWindow;
		std::filesystem::path m_Path;
		std::vector<std::unique_ptr<FileSystemNode>> m_Children;
		bool m_IsDirectory;
	};

	class FileSystemWindow
	{
	public:
		friend class FileSystemNode;

		FileSystemWindow(Tavern::Engine& engine);

		void Render();
		void LoadFileStructure(const std::string& path);

	private:
		Tavern::Engine& m_Engine;

		std::filesystem::path m_ContentPath;
		std::unique_ptr<FileSystemNode> m_Root;

		void LoadDir(FileSystemNode* node, const std::filesystem::path& path);
		void OpenFile(const std::filesystem::path& filePath);
	};
}
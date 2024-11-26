#pragma once

namespace Taverner
{
	class ProjectWindow
	{
	public:
		ProjectWindow(Tavern::Window* window, const std::string& title, int width, int height);

		const bool IsSelectingProject() const;

		void Render();

	private:
		bool m_IsSelectingProject = true;
		Tavern::Window* m_Window;
	};
}
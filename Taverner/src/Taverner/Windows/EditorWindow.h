#pragma once

namespace Taverner
{
	class EditorWindow
	{
	public:
		EditorWindow(Tavern::Window* window, const std::string& title, int width, int height);

		void Render();

	private:
		Tavern::Window* m_Window;
	};
}

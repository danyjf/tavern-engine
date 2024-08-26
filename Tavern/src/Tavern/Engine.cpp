#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Log.h"

namespace Tavern
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::Run()
	{
		Init();

		while (true);
	}

	void Engine::Init()
	{
		Tavern::Log::Init();
		TAVERN_ENGINE_WARN("Initialized Engine Log!");

		// Create glfw window
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// I think this is only needed for mac
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "Tavern Window", NULL, NULL);
		if (window == NULL)
		{
			TAVERN_ENGINE_CRITICAL("Failed to create GLFW window");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		// Initialize glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			TAVERN_ENGINE_CRITICAL("Failed to initialize GLAD");
		}
	}
}

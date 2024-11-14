#include "Window.h"

Window::Window(int width, int height, const std::string& title)
	: width(width), height(height), title(title.c_str())
{
	if (!glfwInit())
	{
		std::cout << "GLFW failed to init!" << std::endl;
		Exit();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		std::cout << "Window failed to create!" << std::endl;
		Exit();
	}

	glfwMakeContextCurrent(window);
}

Window::~Window()
{
	Exit();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

int Window::Exit()
{
	std::cout << "Window is closing!" << std::endl;
	glfwTerminate();
	return -1;
}
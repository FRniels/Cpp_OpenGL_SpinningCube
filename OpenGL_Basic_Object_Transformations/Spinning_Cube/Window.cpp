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

	// glfw accepts 1 user pointer to whatever the user likes. This pointer is retained until the glfw window is destroyed.
	// To be able to access this specific Window class instance from the glfw callbacks, the pointer of this specific class instance is set as the user pointer.
	glfwSetWindowUserPointer(window, this); 
	SetResizeCallback();
}

Window::~Window()
{
	Exit();
}

int Window::Exit()
{
	std::cout << "Window is closing!" << std::endl;
	glfwTerminate();
	return -1;
}

void Window::SetResizeCallback()
{
	glfwSetWindowSizeCallback(window, Callback_Resize);
}

void Window::GetWindowDimensions()
{
	glfwGetWindowSize(window, &width, &height);
}

void Window::Callback_Resize(GLFWwindow* window, int width, int height)
{
	Window* this_window = (Window*)glfwGetWindowUserPointer(window);

	// this_window->are_dimensions_changed = true;

	this_window->width  = width;
	this_window->height = height;

	// std::cout << "Window width: " << this_window->width << " Window height: " << this_window->height << std::endl;

	// SetUniform1f(shader_program, "uWindow_Height", height);
}

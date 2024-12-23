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

	aspect_ratio = (float)width / (float)height;

	glfwMakeContextCurrent(window);

	// glfw accepts 1 user pointer to whatever the user likes. This pointer is retained until the glfw window is destroyed.
	// To be able to access this specific Window class instance from the glfw callbacks, the pointer of this specific class instance is set as the user pointer.
	glfwSetWindowUserPointer(window, this); 
	SetWindowCallbacks();

	InitGLEW();	// Initialize GLEW: FIRST THERE NEEDS TO BE A VALID OPENGL CONTEXT!!! CALL THIS AFTER THE CONTEXT CREATION 
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


void Window::SetWindowCallbacks()
{
	glfwSetWindowSizeCallback(window, Callback_Resize);
	glfwSetKeyCallback(window, Callback_Key);
}

void Window::GetWindowDimensions()
{
	glfwGetWindowSize(window, &width, &height);
}

void Window::InitGLEW()
{
	if (glewInit() != GLEW_OK) // Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION 
	{
		std::cout << "GLEW failed to init!" << std::endl;
		Exit();
	}
}

void Window::Callback_Resize(GLFWwindow* window, int width, int height)
{
	Window* this_window = (Window*)glfwGetWindowUserPointer(window);

	// this_window->are_dimensions_changed = true;

	this_window->width  = width;
	this_window->height = height;
	this_window->aspect_ratio = (float)width / (float)height;

	std::cout << "Window width: " << this_window->width << " Window height: " << this_window->height << " Aspect ratio: " << this_window->aspect_ratio << std::endl;
}

void Window::Callback_Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			std::cout << "Up key pressed" << std::endl;
			break;
		case GLFW_KEY_DOWN:
			std::cout << "Down key pressed" << std::endl;
			break;
		case GLFW_KEY_LEFT:
			std::cout << "Left key pressed" << std::endl;
			break;
		case GLFW_KEY_RIGHT:
			std::cout << "Right key pressed" << std::endl;
			break;
		default:
			break;
		}
	}
}

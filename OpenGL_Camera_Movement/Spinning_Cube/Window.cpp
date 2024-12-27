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
	
	// GLFW Callback user pointer:
	// glfw accepts 1 user pointer to whatever the user likes. This pointer is retained until the glfw window is destroyed.
	// To be able to access this specific Window class instance from the glfw callbacks, the pointer of this specific class instance is set as the user pointer.
	glfwSetWindowUserPointer(window, this);

	glfwSetWindowSizeCallback(window, Callback_Resize);
	// SetWindowCallbacks();

	InitGLEW();	// Initialize GLEW: FIRST THERE NEEDS TO BE A VALID OPENGL CONTEXT!!! CALL THIS AFTER THE CONTEXT CREATION 
}

Window::~Window()
{
	Exit();
}

void Window::InitGLEW()
{
	if (glewInit() != GLEW_OK) // Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION 
	{
		std::cout << "GLEW failed to init!" << std::endl;
		Exit();
	}
}

//void Window::SetWindowCallbacks()
//{
//	// glfw accepts 1 user pointer to whatever the user likes. This pointer is retained until the glfw window is destroyed.
//	// To be able to access this specific Window class instance from the glfw callbacks, the pointer of this specific class instance is set as the user pointer.
//	glfwSetWindowUserPointer(window, this);
//
//	glfwSetWindowSizeCallback(window, Callback_Resize);
//	// glfwSetKeyCallback(window, Callback_Key); // THE CAMERA SET'S THE KEY CALLBACK FOR NOW
//}

void Window::GetWindowDimensions()
{
	glfwGetWindowSize(window, &width, &height);
}


void Window::Callback_Resize(GLFWwindow* window, int width, int height)
{
	Window* this_window = (Window*)glfwGetWindowUserPointer(window);
	 
	this_window->width        = width;
	this_window->height       = height;
	this_window->aspect_ratio = (float)width / (float)height;

	std::cout << "Window width: " << this_window->width << " Window height: " << this_window->height << " Aspect ratio: " << this_window->aspect_ratio << std::endl;
}

//void Window::Callback_Key(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (action == GLFW_PRESS) // THIS WILL ALWAYS BE TRUE THE FIRST TIME THE KEY IS PRESSED, EVEN IF IT'S HELD DOWN
//	{
//		switch (key)
//		{
//		case GLFW_KEY_UP:
//			std::cout << "Up key pressed" << std::endl;
//			break;
//		case GLFW_KEY_DOWN:
//			std::cout << "Down key pressed" << std::endl;
//			break;
//		case GLFW_KEY_LEFT:
//			std::cout << "Left key pressed" << std::endl;
//			break;
//		case GLFW_KEY_RIGHT:
//			std::cout << "Right key pressed" << std::endl;
//			break;
//		default:
//			break;
//		}
//	}
//	else if (action == GLFW_REPEAT) // HOW DO YOU REDUCE THE DELAY BEFORE THE KEY IS REGISTERED AS GLFW_REPEAT ??? 
//	{
//		switch (key)
//		{
//		case GLFW_KEY_UP:
//			std::cout << "Up key held down" << std::endl;
//			break;
//		case GLFW_KEY_DOWN:
//			std::cout << "Down key held down" << std::endl;
//			break;
//		case GLFW_KEY_LEFT:
//			std::cout << "Left key held down" << std::endl;
//			break;
//		case GLFW_KEY_RIGHT:
//			std::cout << "Right key held down" << std::endl;
//			break;
//		default:
//			break;
//		}
//	}
//}

void Window::SetKeyCallback(KeyCallback callback) 
{ 
	key_callback = callback;

	// Using a lambda callback function that calls the callback function that is registered inside the key_callback variable. 
	// (The camera will set this key_callback for example)
	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (window && window->key_callback)
		{
			window->key_callback(key, scancode, action, mods);
		}
	});
}

int Window::Exit()
{
	std::cout << "Window is closing!" << std::endl;
	glfwTerminate();
	return -1;
}

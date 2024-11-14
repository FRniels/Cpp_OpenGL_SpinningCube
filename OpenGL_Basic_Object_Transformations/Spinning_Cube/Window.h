#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "GLFW/glfw3.h"

// Info about inline member functions: https://isocpp.org/wiki/faq/inline-functions#inline-member-fns

class Window
{
private:
	GLFWwindow* window;
	int width, height;
	const char* title;
	// bool are_dimensions_changed = false;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	int  GetWindowWidth()  { return width;  }
	int  GetWindowHeight() { return height; }
	void SwapBuffers();			// Swap front and back buffers 
	void PollEvents();		    // Poll and process events
	bool ShouldWindowClose();
	int  Exit();
	inline GLFWwindow* GetWindow() const { return window; }

private:
	void SetResizeCallback();
	void GetWindowDimensions();

	static void Callback_Resize(GLFWwindow* window, int width, int height);
};

inline void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

inline void Window::PollEvents()
{
	glfwPollEvents();
}

inline bool Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(window) ? true : false;
}

#endif; // WINDOW_H
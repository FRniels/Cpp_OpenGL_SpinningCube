#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "GLFW/glfw3.h"

class Window
{
private:
	GLFWwindow* window;
	int width, height;
	const char* title;
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void SwapBuffers();	// Swap front and back buffers 
	void PollEvents();  // Poll and process events
	int Exit();
	inline GLFWwindow* GetWindow() const { return window; }
};

#endif; // WINDOW_H
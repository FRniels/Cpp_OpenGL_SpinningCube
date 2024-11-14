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

	int  GetWindowWidth()  { return width;  }
	int  GetWindowHeight() { return height; }
	void SwapBuffers();							// Swap front and back buffers 
	void PollEvents();							// Poll and process events
	bool ShouldWindowClose();
	int  Exit();
	inline GLFWwindow* GetWindow() const { return window; }

private:
	void GetWindowDimensions();

};

#endif; // WINDOW_H
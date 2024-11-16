#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
// The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"	 // The glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"	
#include "Timer.h"

// Info about inline member functions: https://isocpp.org/wiki/faq/inline-functions#inline-member-fns

class Window
{
private:
	GLFWwindow* window;
	int width, height;
	const char* title;
	// bool are_dimensions_changed = false;
	Time_t window_time;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	int  GetWindowWidth()		  const	{ return width; }
	int  GetWindowHeight()        const	{ return height; }
	void InitTime()						{ window_time.Init(); }
	void UpdateTime()					{ window_time.Update(); }
	const Time_t& GetWindowTime() const { return window_time;  }
	void SwapBuffers();													// Swap front and back buffers 
	void PollEvents();													// Poll and process events
	bool ShouldWindowClose();
	int  Exit();
	inline GLFWwindow* GetWindow() const { return window; }

private:
	void SetResizeCallback();
	void GetWindowDimensions();
	void InitGLEW();			 // Initialize GLEW: FIRST THERE NEEDS TO BE A VALID OPENGL CONTEXT!!! CALL THIS AFTER THE CONTEXT CREATION 

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
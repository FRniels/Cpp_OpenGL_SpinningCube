#ifndef WINDOW_H
#define WINDOW_H

#include <functional> // Needed for creating function prototypes
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
	float aspect_ratio;
	bool is_aspect_ratio_changed;
	const char* title;
	Time_t window_time;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	inline GLFWwindow* GetWindow() const { return window; }
	int  GetWindowWidth()		   const { return width; }
	int  GetWindowHeight()         const { return height; }
	float GetAspectRatio()         const { return aspect_ratio; }
	void InitTime()						 { window_time.Init(); }
	void UpdateTime()					 { window_time.Update(); }
	const Time_t& GetWindowTime()  const { return window_time;  }
	void SwapBuffers();			  // Swap front and back buffers 
	void PollEvents();			  // Poll and process events
	bool ShouldWindowClose();
	int  Exit();

	// Function prototype for the GLFW KeyCallback
	typedef std::function<void(int, int, int, int)> KeyCallback;
	// Register a callback function for handling key strokes
	void SetKeyCallback(KeyCallback callback);

private:
	void InitGLEW();			 // Initialize GLEW: FIRST THERE NEEDS TO BE A VALID OPENGL CONTEXT!!! CALL THIS AFTER THE CONTEXT CREATION 
	void GetWindowDimensions();

	KeyCallback key_callback;
	// void SetWindowCallbacks();
	static void Callback_Resize(GLFWwindow* window, int width, int height);
	// static void Callback_Key(GLFWwindow* window, int key, int scancode, int action, int mods);
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
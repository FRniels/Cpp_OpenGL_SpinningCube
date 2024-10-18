#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GL/glew.h"    
#include "GLFW/glfw3.h"

#include "GL_ErrorHandeling.h"


int main()
{
    GLFWwindow* window;

	/*Initialize the library*/
	if (!glfwInit())
		return -1;

	/*Create windowed mode window and it's openGl context*/
	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/*Set the window context to be the current context*/
	glfwMakeContextCurrent(window);

	/*Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION*/
	if (glewInit() != GLEW_OK)
		std::cout << "Error with initializing GLEW!" << std::endl;

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window))
	{
		/*RENDER*/
		glClearColor(0.996F, 0.54F, 0.094F, 0.0F); // Orange => glClearColor doesn't set the gl state, it mearly sets the color to be used to clear the whole buffer.
		GL_Call(glClear(GL_COLOR_BUFFER_BIT));

		GL_Call(glBegin(GL_TRIANGLES));
		GL_Call(glVertex2f(0.0f, 0.5f));
		GL_Call(glVertex2f(-0.5f, -0.5f));
		GL_Call(glVertex2f(0.5f, -0.5f));
		GL_Call(glEnd());

		/*Swap front and back buffers*/
		glfwSwapBuffers(window);

		/*Poll and process events*/
		glfwPollEvents();

	}

	glfwTerminate();

    return 0;
}
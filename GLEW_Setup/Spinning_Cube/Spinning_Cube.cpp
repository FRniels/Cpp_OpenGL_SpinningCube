// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>
//This must be included before any other opengl things are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"    //This header file contains the function pointer to OpenGl functions
#include "GLFW/glfw3.h"

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
		glClearColor(0.996F, 0.54F, 0.094F, 0.0F); // Orange
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		/*Swap front and back buffers*/
		glfwSwapBuffers(window);

		/*Poll and process events*/
		glfwPollEvents();

	}

	glfwTerminate();

    return 0;
}

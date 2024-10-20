// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

//This must be included before any other opengl things are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"    //This header file contains the function pointer to OpenGl functions
#include "GLFW/glfw3.h"

#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"

unsigned int GL_CreateShaderProgram(const std::string& filepPath);
void GL_ClearScreen(void);
void DrawTriangle(void);

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

	/* Create Shader Program */
	unsigned int shader_program = GL_CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader");
	GL_Call(glUseProgram(shader_program));

	/*Before an uniform can be declared, the program needs to be bound*/
	GL_Call(int uniformLocation_color = glGetUniformLocation(shader_program, "u_Color"));

	/*
	  Note: Keep in mind that an uniform is removed by the compiler if you don't use it!
			This will trigger this ASSERT(), so watch out for this because sometimes
			you forget to remove an unused uniform or have one declared for later usage or another situation.
	*/
	ASSERT(uniformLocation_color != -1);
	GL_Call(glUniform4f(uniformLocation_color, 0.0f, 1.0f, 1.0f, 1.0f)); // Set the shader uniform value

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window))
	{
		/*RENDER*/
		GL_ClearScreen();
		DrawTriangle();

		/*Swap front and back buffers*/
		glfwSwapBuffers(window);

		/*Poll and process events*/
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}

unsigned int GL_CreateShaderProgram(const std::string& filepPath)
{
	ShaderProgramSource shaderProgramSources = ParseShader(filepPath);
	return CreateShaderProgram(shaderProgramSources.VertexShader, shaderProgramSources.FragmentShader);
}

void GL_ClearScreen(void)
{
	glClearColor(0.996F, 0.54F, 0.094F, 0.0F); // Orange
	GL_Call(glClear(GL_COLOR_BUFFER_BIT));
}

void DrawTriangle(void)
{
	GL_Call(glBegin(GL_TRIANGLES));
	GL_Call(glVertex2f(0.0f, 0.5f));
	GL_Call(glVertex2f(-0.5f, -0.5f));
	GL_Call(glVertex2f(0.5f, -0.5f));
	glEnd();
}

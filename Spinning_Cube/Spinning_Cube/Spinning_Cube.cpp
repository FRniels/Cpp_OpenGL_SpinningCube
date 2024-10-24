// THIS IS THE MAIN PROJECT

// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>
//This must be included before any other opengl things are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"    //This header file contains the function pointer to OpenGl functions
#include "GLFW/glfw3.h"

#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_Buffers.h"
#include "GL_Draw.h"

unsigned int GL_CreateShaderProgram(const std::string& filepPath);
void GL_Render(void);

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

	float positions[] = //Rectangle
	{
		-0.5f, -0.5f, //Bottom left corner
		 0.5f, -0.5f, //Bottom right corner
		 0.5f,  0.5f, //Top right corner
		-0.5f,  0.5f, //Top left corner
	};
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GL_VertexBuffer bufferV(positions, 4 * 2 * sizeof(float));

	/*Data layout*/
	GL_Call(glEnableVertexAttribArray(0));
	GL_Call(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	GL_ElementBuffer bufferE(indices, 2 * 3 * sizeof(unsigned int));

	// SHADERS
	unsigned int shader_program = GL_CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// Set shader uniforms => Note: uniforms should only be set from the user (cpu) code and not from within the shader code itself
	vec4f color_vec = { 0.0f, 1.0f, 1.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Color", color_vec);       // Note: vec4 will be passed as pointer as it is an array

	vec4f position_vec = { 0.25f, 0.0f, 0.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Position", position_vec); // Note: vec4 will be passed as pointer as it is an array

	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F }; // Orange
	GL_ClearColor(clear_color);

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window))		// Loop until the user closes the window
	{
		/*RENDER*/								
		GL_Render();							// Render the scene
												
		glfwSwapBuffers(window);				// Swap front and back buffers 
												
		glfwPollEvents();						// Poll and process events

	}

	glfwTerminate();

    return 0;
}

unsigned int GL_CreateShaderProgram(const std::string& filepPath)
{
	ShaderProgramSource shaderProgramSources = ParseShader(filepPath);
	return CreateShaderProgram(shaderProgramSources.VertexShader, shaderProgramSources.FragmentShader);
}

void GL_Render(void)
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	GL_ClearScreen(clear_color);

	GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

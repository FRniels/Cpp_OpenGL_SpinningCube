// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

//The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h" // This glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "GL_User_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_Draw.h"

unsigned int GL_CreateShaderProgram(const std::string& filepPath);
void GL_Render(void);

int main()
{
    GLFWwindow* window;

	if (!glfwInit())										     // Initialize the library 
		return -1;

	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);   // Create windowed mode window and it's openGl context 
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);                              // Set the window context to be the current context 

	if (glewInit() != GLEW_OK)                                   // Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION 
		std::cout << "Error with initializing GLEW!" << std::endl;

	unsigned int shader_program = GL_CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// Set shader uniforms => Note: uniforms should only be set from the user (cpu) code and not from within the shader code itself
	vec4f color_vec = { 0.0f, 1.0f, 1.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Color", color_vec);       // Note: vec4 will be passed as pointer as it is an array

	vec4f position_vec = { 0.25f, 0.0f, 0.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Position", position_vec); // Note: vec4 will be passed as pointer as it is an array

	/* RENDER LOOP */
	while (!glfwWindowShouldClose(window))                       // Loop until the user closes the window
	{
		GL_Render();											 // Render the scene

		glfwSwapBuffers(window);                                 // Swap front and back buffers 

		glfwPollEvents();                                        // Poll and process events
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
	DrawTriangle();
}

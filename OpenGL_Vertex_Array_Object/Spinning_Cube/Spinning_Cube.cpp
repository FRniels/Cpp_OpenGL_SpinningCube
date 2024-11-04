// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

//The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h" // This glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "GL_User_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_Buffers.h"
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

	// Vertex array: Instead of binding the vertex and element buffer directly to the OpenGL context, those buffers can be
	//				 bound to a Vertex Array Object (VAO). IMPORTANT: to bind the vertex/element buffer to the vao, the vao
	//               needs to be bound to the OpenGL context before binding the vertex/element buffer. 
	//               This vao can than be unbound when not needed and bound to the OpenGL context later on when needed. 
	//				 This allows for configuring vao's upfront and just bind the one that is needed before drawing.
	unsigned int vertex_array_object;
	GL_Call(glGenVertexArrays(1, &vertex_array_object));
	GL_Call(glBindVertexArray(vertex_array_object));

	GL_VertexBuffer bufferV(positions, 4 * 2 * sizeof(float));       // The vertex buffer is bound to the OpenGL contect on instantiation

	/*Data layout*/
	GL_Call(glEnableVertexAttribArray(0));
	GL_Call(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	GL_ElementBuffer bufferE(indices, 2 * 3 * sizeof(unsigned int)); // The element buffer is bound to the OpenGL contect on instantiation

	unsigned int shader_program = GL_CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// Set shader uniforms => Note: uniforms should only be set from the user (cpu) code and not from within the shader code itself
	vec4f color_vec = { 0.0f, 1.0f, 1.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Color", color_vec);       // Note: vec4 will be passed as pointer as it is an array

	vec4f position_vec = { 0.25f, 0.0f, 0.0f, 1.0f };
	SetUniform_vec4(shader_program, "u_Position", position_vec); // Note: vec4 will be passed as pointer as it is an array

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	// 
	// Unbind all buffers including the vao and the shader program.
	// When this specific vao is needed when drawing, this vao can be bound to the OpenGL context at that moment.
	// The shader program is not stored inside the vao so it needs to be bound to the OpenGL context seperately.
	GL_Call(glBindVertexArray(0));
	bufferV.Unbound();
	bufferE.Unbound();
	GL_Call(glUseProgram(0));


	/* RENDER LOOP */
	while (!glfwWindowShouldClose(window))                       // Loop until the user closes the window
	{
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing.
		GL_Call(glBindVertexArray(vertex_array_object));
		GL_Call(glUseProgram(shader_program));
		GL_Render();											 // Render the scene

		glfwSwapBuffers(window);                                 // Swap front and back buffers 

		glfwPollEvents();                                        // Poll and process events
	}

	// Clean-up:
	bufferV.Delete();
	bufferE.Delete();
	GL_Call(glDeleteProgram(shader_program));
	GL_Call(glDeleteVertexArrays(1, &vertex_array_object));

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

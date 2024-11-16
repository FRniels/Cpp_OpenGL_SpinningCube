// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

//The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"     // This glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "GL_User_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_VertexArray.h"
#include "GL_VertexBufferLayout.h"
#include "GL_Buffers.h"
#include "GL_Draw.h"



void Callback_Resize(GLFWwindow* window, int width, int height);
void GL_Render(void);


vec2i u_window_coo = { 0, 0 }; // Global so that the window resize callback has access to this vec2f => TO DO: CAN I PASS AN EXTRA ARGUMENT TO THE CALLBACK ??

unsigned int shader_program;

int main()
{
	GLFWwindow* window;

	if (!glfwInit())										       // Initialize the library 
		return -1;

	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);     // Create windowed mode window and it's openGl context 
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);                                 // Set the window context to be the current context 

	glfwSetWindowSizeCallback(window, Callback_Resize);

	if (glewInit() != GLEW_OK)                                      // Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION 
		std::cout << "Error with initializing GLEW!" << std::endl;


	float positions[] =       // Rectangle
	{ 
		-0.5f, -0.5f,         // Bottom left corner
		 0.5f, -0.5f,		  // Bottom right corner
		 0.5f,  0.5f,		  // Top right corner
		-0.5f,  0.5f,         // Top left corner
	};

	float vertices[] =		  // A vertex can also hold other data than pure position data such as color data.
	{
		//Position:		Color:
		-0.5f, -0.5f,	0.0f, 0.5f, 0.5f, 1.0f, // Bottom left corner
		 0.5f, -0.5f,	0.0f, 0.5f, 0.5f, 1.0f, // Bottom right corner
		 0.5f,  0.5f,	0.0f, 0.5f, 0.5f, 1.0f, // Top right corner
		-0.5f,  0.5f,	0.0f, 0.5f, 0.5f, 1.0f  // Top left corner
	};

	unsigned int indices[] =  // Rectangle indices
	{
		0, 1, 2,
		2, 3, 0
	};

	// Vertex array: 
	//     Instead of binding the vertex and element buffer directly to the OpenGL context, those buffers can be
	//	   bound to a Vertex Array Object (VAO). 
	//	   IMPORTANT: 
	//	       To bind the vertex/element buffer to the vao, the vao needs to be bound to the OpenGL context before binding the vertex/element buffer. 
	//		   This vao can than be unbound when not needed and bound to the OpenGL context later on when needed. 
	//		   This allows for configuring vao's upfront and just bind the one that is needed before drawing.
	GL_Vertex_Array vertex_array;
	// unsigned int vertex_array_object;
	// GL_Call(glGenVertexArrays(1, &vertex_array_object));
	// GL_Call(glBindVertexArray(vertex_array_object));

	// GL_VertexBuffer bufferV(positions, 4 * 2 * sizeof(float));       // The vertex buffer is bound to the OpenGL context on instantiation
	GL_VertexBuffer bufferV(vertices, 4 * 6 * sizeof(float));

	// Data layout
	GL_VertexBufferLayout layout_bufferV;
	layout_bufferV.Push<float>(2);				// Push the amount of floats per vertex that are used for the vertex position
	// GL_Call(glEnableVertexAttribArray(0));
	// GL_Call(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
	layout_bufferV.Push<float>(4);				// Push the amount of floats per vertex that are used for the vertex color

	vertex_array.AddBuffer(bufferV, layout_bufferV);

	GL_ElementBuffer bufferE(indices, 2 * 3); // The element buffer is bound to the OpenGL contect on instantiation


	shader_program = CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// Set shader uniforms => Note: uniforms should only be set from the user (cpu) code and not from within the shader code itself
	// Vertex shader uniforms:
	vec4f position_vec = { 0.25f, 0.0f, 0.0f, 1.0f };
	SetUniform(shader_program, "u_Position", position_vec);          // Note: vec4 will be passed as pointer as it is an array
	
	// Fragment shader uniforms:
	vec4f color_vec = { 0.0f, 1.0f, 1.0f, 1.0f };
	// SetUniform(shader_program, "u_Color",        color_vec);       // Note: vec4 will be passed as pointer as it is an array => Not using this uniform in the shader anymore
	
	glfwGetWindowSize(window, NULL, &u_window_coo[1]);
	SetUniform(shader_program, "uWindow_Height", u_window_coo[1]);

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	// 
	// Unbind all buffers including the vao and the shader program.
	// When this specific vao is needed when drawing, this vao can be bound to the OpenGL context at that moment.
	// The shader program is not stored inside the vao so it needs to be bound to the OpenGL context seperately.
	GL_Vertex_Array::Unbind();
	// GL_Call(glBindVertexArray(0));
	GL_VertexBuffer::Unbind();
	GL_ElementBuffer::Unbind();
	GL_Call(glUseProgram(0));


	// RENDER LOOP 
	while (!glfwWindowShouldClose(window))                       // Loop until the user closes the window
	{
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		vertex_array.Bind();
		// GL_Call(glBindVertexArray(vertex_array_object));
		GL_Call(glUseProgram(shader_program));					 // Bind the required shader program to th OpenGL context

		GL_Render();											 // Render the scene

		glfwSwapBuffers(window);                                 // Swap front and back buffers 

		glfwPollEvents();                                        // Poll and process events
	}

	// Clean-up:
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
	// GL_Call(glDeleteVertexArrays(1, &vertex_array_object));
	GL_Call(glDeleteProgram(shader_program));

	glfwTerminate();

    return 0;
}

void Callback_Resize(GLFWwindow* window, int width, int height)
{
	std::cout << "Window width: " << width << " Window height: " << height << std::endl;
	u_window_coo[0] = width;
	u_window_coo[1] = height;

	SetUniform(shader_program, "uWindow_Height", height); // TO DO: Save the handle the first time and use this handle to search for all following calls to SetUniform() to avoid the overhead of search by string name
}

void GL_Render(void)
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	GL_ClearScreen(clear_color);

	GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

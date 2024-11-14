// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

//The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"     // This glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "Window.h"
#include "GL_User_Types.h" // TO DO: MOVE THESE TYPES TO MATH TYPES 
#include "Math_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_VertexArray.h"
#include "GL_VertexBufferLayout.h"
#include "GL_Buffers.h"
#include "GL_Draw.h"



// void Callback_Resize(GLFWwindow* window, int width, int height);
void Render(void);


vec2i u_window_coo = { 0, 0 }; // Global so that the window resize callback has access to this vec2f => TO DO: CAN I PASS AN EXTRA ARGUMENT TO THE CALLBACK ??

unsigned int shader_program;

int main()
{
	Window window(800, 600, "Spinning cube");
	// glfwSetWindowSizeCallback(window.GetWindow(), Callback_Resize);

	if (glewInit() != GLEW_OK) // Initialize GLEW: YOU FIRST NEED TO HAVE A VALID OPENGL CONTEXT!!! SO CALL THIS AFTER THE CONTEXT CREATION 
	{
		std::cout << "GLEW failed to init!" << std::endl;
		window.Exit();
	}


	float positions[] =       // Rectangle
	{ 
		-0.5f, -0.5f,         // Bottom left corner
		 0.5f, -0.5f,		  // Bottom right corner
		 0.5f,  0.5f,		  // Top right corner
		-0.5f,  0.5f,         // Top left corner
	};
	unsigned int indices[] =  // Rectangle indices
	{
		0, 1, 2,
		2, 3, 0
	};

	
	GL_Vertex_Array vertex_array;
	GL_VertexBuffer bufferV(positions, 4 * 2 * sizeof(float));       // The vertex buffer is bound to the OpenGL context on instantiation
	GL_VertexBufferLayout layout_bufferV;
	layout_bufferV.Push<float>(2);									 // Push a layout of 2 * GL_FLOAT in the layout vector
	vertex_array.AddBuffer(bufferV, layout_bufferV);
	GL_ElementBuffer bufferE(indices, 2 * 3 * sizeof(unsigned int)); // The element buffer is bound to the OpenGL contect on instantiation

	shader_program = CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// Set shader uniforms => Note: uniforms should only be set from the user (cpu) code and not from within the shader code itself
	// Vertex shader uniforms:
	vec4f position_vec = { 0.25f, 0.0f, 0.0f, 1.0f };
	GL_Uniform u_position = GetUniform(shader_program, "u_Position");
	SetUniform4f(shader_program, u_position.Get_Handle(), position_vec);
	

	// float translate_x = 0.5F;
	// float translate_y = 0.5F;
	TranslationMatrix4f mat_translation; 
	/*
	{
		0.0f, 0.0f, 0.0f, translate_x,
		0.0f, 0.0f, 0.0f, translate_y,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};
	*/
	vec3f translation_vec = { 0.5f, 0.5f, 0.0f };
	mat_translation.SetTranslation3f(translation_vec);

	// Fragment shader uniforms:
	GL_Uniform u_window_height = GetUniform(shader_program, "uWindow_Height");
	SetUniform1f(shader_program, u_window_height.Get_Handle(), window.GetWindowHeight());

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	GL_Vertex_Array::Unbind();
	GL_VertexBuffer::Unbind();
	GL_ElementBuffer::Unbind();
	GL_Call(glUseProgram(0));


	// RENDER LOOP 
	while (!window.ShouldWindowClose())              // Loop until the user closes the window
	{
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		vertex_array.Bind();
		GL_Call(glUseProgram(shader_program));    	 // Bind the required shader program to th OpenGL context

		Render();									 // Render the scene

		window.SwapBuffers();

		window.PollEvents();
	}

	// Clean-up:
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
	GL_Call(glDeleteProgram(shader_program));

	window.Exit();

    return 0;
}

//void Callback_Resize(GLFWwindow* window, int width, int height)
//{
//	// std::cout << "Window width: " << width << " Window height: " << height << std::endl;
//	u_window_coo[0] = width;
//	u_window_coo[1] = height;
//
//	SetUniform1f(shader_program, "uWindow_Height", height); // TO DO: Save the handle the first time and use this handle to search for all following calls to SetUniform() to avoid the overhead of search by string name
//}

void Render(void)
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	GL_ClearScreen(clear_color);

	GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}
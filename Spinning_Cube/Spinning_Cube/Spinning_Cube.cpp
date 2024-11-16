// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

// The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"     // The glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "Window.h"
#include "GL_User_Types.h" 
#include "Math_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_VertexArray.h"
#include "GL_VertexBufferLayout.h"
#include "GL_Buffers.h"
#include "GL_Draw.h"
#include "Timer.h"



void Render(void);

int main()
{
	Window window(800, 800, "Spinning cube"); // Square window: Aspect ration is not implemented yet

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

	unsigned int shader_program = CreateShaderProgram("../Resources/Shaders/Shader_Vertex_Fragment.shader"); // Create Shader Program 
	UseShaderProgram(shader_program);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// SCALING
	ScalingMatrix4f mat_scaling;
	vec3f scaling_vec = { 0.5f, 0.5f, 1.0f };
	mat_scaling.SetScaling3f(scaling_vec);									          // Set the X, Y and Z scaling values in the translation matrix

	GL_Uniform u_scaling_mat = GetUniform(shader_program, "u_Scaling_mat");
	SetUniformMat4f(shader_program, u_scaling_mat.Get_Handle(), mat_scaling);         // Pass the rotation matrix to the shader
	
	// ROTATION
	RotationMatrix4f mat_rotation_z;
	// mat_rotation_z.SetRotation(45.0f, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);
	mat_rotation_z.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);

	GL_Uniform u_rotation_z_mat = GetUniform(shader_program, "u_RotationZ_mat");
	SetUniformMat4f(shader_program, u_rotation_z_mat.Get_Handle(), mat_rotation_z);   // Pass the rotation matrix to the shader

	// TRANSLATION
	TranslationMatrix4f mat_translation; 
	vec3f translation_vec = { 0.25f, 0.25f, 0.0f };
	mat_translation.SetTranslation3f(translation_vec);								  // Set the X, Y and Z translation values in the translation matrix

	GL_Uniform u_translation_mat = GetUniform(shader_program, "u_Translation_mat"); 
	SetUniformMat4f(shader_program, u_translation_mat.Get_Handle(), mat_translation); // Pass the translation matrix to the shader


	// FRAGMENT SHADER UNIFORMS:
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
	float rotation_z = 0.0f;
	Timer translation_timer(window.GetWindowTime(), FPS_60_PERIOD);
	window.InitTime();

	while (!window.ShouldWindowClose())              // Loop until the user closes the window
	{
		window.UpdateTime();

		if (translation_timer.IsTimerExpired()) 
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			// UPDATE THE ROTATION Z MATRIX AND PASS THE UPDATED ROTATION MATRIX TO THE VERTEX SHADER.
			++rotation_z;
			mat_rotation_z.SetRotation(rotation_z, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);
			SetUniformMat4f(shader_program, u_rotation_z_mat.Get_Handle(), mat_rotation_z); 

			translation_timer.Reset();
		}

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

void Render(void)
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	GL_ClearScreen(clear_color);

	GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

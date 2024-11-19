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

	// TEST: MATRIX MULTIPLICATION OPERATOR OVERLOAD
	TranslationMatrix4f trans;
	vec3f trans_test = { 2.0f, 2.5f, 1.0f };
	trans.SetTranslation3f(trans_test);
	RotationMatrix4f rot;

	ScalingMatrix4f scale;
	vec3f scale_test = { 3.0f, 3.0f, 3.0f };
	scale.SetScaling3f(scale_test);
	Matrix4f transformation_mat4 = trans * rot * scale;

	Matrix4f debug_breakpoint_mat;

	float floor_vertices[] =
	{
		//Position:		       Color:
		 0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 0. Top right
		-0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 1. Top left
		-0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 2. Bottom left
		 0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f  // 3. Bottom right
	};
	float floor_indices[] =	   // Counter clockwise
	{
		0, 1, 2,			   // Top right, top left, bottom left
		2, 3, 0                // Bottom left, bottom left, top right
	};

	float cube_vertices[] =	   // BLENDER .ply EXPORT
	{
		-0.5f,  0.5f,  0.5f,   // 0. Front: Top left
		 0.5f,  0.5f,  0.5f,   // 1. Front: Top right
		 0.5f,  0.5f, -0.5f,   // 2. Back:  Top right
		-0.5f,  0.5f, -0.5f,   // 3. Back:  Top left
		-0.5f, -0.5f, -0.5f,   // 4. Back:  Bottom left
		 0.5f, -0.5f, -0.5f,   // 5. Back:  Bottom right
		 0.5f, -0.5f,  0.5f,   // 6. Front: Bottom right
		-0.5f, -0.5f,  0.5f    // 7. Front: Bottom left
	}; 
	unsigned int cube_indices[] = // Counter clockwise		
	{
		// BLENDER EXPORT: Fails to render, except for 1 triangle => 4, 0, 1 doesn't make any sense to me ???
		/*4, 0, 1, 2, 3,
		4, 4, 3, 2, 5,
		4, 5, 2, 1, 6,
		4, 6, 7, 4, 5,
		4, 7, 0, 3, 4,
		4, 6, 1, 0, 7*/

		// Cube order explanation: https://stackoverflow.com/questions/8142388/in-what-order-should-i-send-my-vertices-to-opengl-for-culling
		// FRONT FACE:
		// TRIANGLE 1:
		1, 0, 7,       // Front Top right, Front top left, Front bottom left
		// TRIANGLE 2:
		7, 6, 1,       // Front bottom left, Front bottom right, Front top right
		 
		// BACK FACE:
		// TRIANGLE 1:
		2, 5, 4,       // Back Top right, Back botom right, Back bottom left
		// TRIANGLE 2:
		4, 3, 2,       // Back bottom left, Back top left, Back top right
		 
		// TOP FACE:
		// TRIANGLE 1:
		2, 3, 0,       // Back top right, Back top left, Front top left
		// TRIANGLE 2:
		0, 1, 2,       // Front top left, Front top right, Back top right

		// BOTTOM FACE: 
		// TRIANGLE 1:
		6, 7, 4,       // Front bottom right, Front bottom left, Back bottom left
		// TRIANGLE 2:
		4, 5, 6,       // Back bottom left, Back bottom right, Front bottom right

		// RIGHT FACE:
		// TRIANGLE 1:
		2, 1, 6,       // Back top right, Front top right, Front bottom right
		// 6, 1, 2,
		// TRIANGLE 2:
		6, 5, 2,       // Front bottom right, Back bottom right, Back top right
		// 2, 5, 6,

		// LEFT FACE:
		// TRIANGLE 1:
		0, 3, 4,	   // Front top left, Back top left, Back bottom left
		// TRIANGLE 2:
		4, 7, 0        // Back bottom left, Front bottom left, Front top left
	};

	
	GL_Vertex_Array vertex_array;
	GL_VertexBuffer bufferV(cube_vertices, 8 * 3 * sizeof(float));   // The vertex buffer is bound to the OpenGL context on instantiation
	GL_VertexBufferLayout layout_bufferV;
	layout_bufferV.Push<float>(3);									 // Push the amount of floats per vertex that are used for the vertex position
	// layout_bufferV.Push<float>(4);									// Push the amount of floats per vertex that are used for the vertex color
	vertex_array.AddBuffer(bufferV, layout_bufferV);
	GL_ElementBuffer bufferE(cube_indices, 12 * 3);				     // The element buffer is bound to the OpenGL contect on instantiation

	unsigned int shader_program_cube = CreateShaderProgram("../Resources/Shaders/Cube.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_cube);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// SCALING
	ScalingMatrix4f mat_scaling;
	vec3f scaling_vec = { 1.0f, 1.0f, 1.0f };
	mat_scaling.SetScaling3f(scaling_vec);									          // Set the X, Y and Z scaling values in the translation matrix

	GL_Uniform u_scaling_mat = GetUniform(shader_program_cube, "u_Scaling_mat");
	SetUniformMat4f(shader_program_cube, u_scaling_mat.Get_Handle(), mat_scaling);         // Pass the rotation matrix to the shader
	
	// ROTATION
	RotationMatrix4f mat_rotation_y;
	// mat_rotation_y.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_X_AXIS);
	// mat_rotation_z.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);
	// mat_rotation_z.SetRotation(90.0f, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);

	GL_Uniform u_rotation_y_mat = GetUniform(shader_program_cube, "u_RotationY_mat");
	SetUniformMat4f(shader_program_cube, u_rotation_y_mat.Get_Handle(), mat_rotation_y);   // Pass the rotation matrix to the shader

	// TRANSLATION
	TranslationMatrix4f mat_translation; 
	vec3f translation_vec = { 0.0f, 0.0f, 2.5f };
	mat_translation.SetTranslation3f(translation_vec);								  // Set the X, Y and Z translation values in the translation matrix

	GL_Uniform u_translation_mat = GetUniform(shader_program_cube, "u_Translation_mat");
	SetUniformMat4f(shader_program_cube, u_translation_mat.Get_Handle(), mat_translation); // Pass the translation matrix to the shader

	// PROJECTION
	ProjectionMatrix4f projection_mat;
	projection_mat.SetFOV(90.0f);

	GL_Uniform u_projection_mat = GetUniform(shader_program_cube, "u_Projection_mat");     // Pass the projection matrix to the shader
	SetUniformMat4f(shader_program_cube, u_projection_mat.Get_Handle(), projection_mat);   // IF THE CUBE IS NOT VISIBLE, TRANSLATE IT ALONG THE POSITIVE Z AXIS, THE CUBE WILL PROBABLY BE DEFINED IN CLIP SPACE COORDINATES [-1, 1] 
																					  // AND THUS BE TO CLOSE OR BEHIND THE 'CAMERA' AFTER PROJECTION
	// FRAGMENT SHADER UNIFORMS:
	GL_Uniform u_window_height = GetUniform(shader_program_cube, "uWindow_Height");
	SetUniform1f(shader_program_cube, u_window_height.Get_Handle(), window.GetWindowHeight());

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	GL_Vertex_Array::Unbind();
	GL_VertexBuffer::Unbind();
	GL_ElementBuffer::Unbind();
	GL_Call(glUseProgram(0));


	// FACE CULLING:
	// When having a closed mesh, avoid running the fragment shader on all fragments that are behind another fragment. (Fragment with lower -Z is closer to the viewer)
	// This doesn't waste unnecessary calculations and thus boost performance.
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// DEPTH TESTING		 // TO DO: RESEARCH DEPTH TEST => IF DEPTH TEST IS ENABLED, THE CUBE DISAPPEARS
	// Enable depth test     // THE DEPTH MUST BE CLEARED EACH FRAME => SEE THE RENDER FUNCTION FOR THE CHANGE IN CODE!
	// glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	// glDepthFunc(GL_LESS);

	// RENDER LOOP 
	float rotation_y = 0.0f;
	Timer translation_timer(window.GetWindowTime(), 1/ 200.0); // FPS_60_PERIOD
	window.InitTime();

	while (!window.ShouldWindowClose())              // Loop until the user closes the window
	{
		window.UpdateTime();

		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		vertex_array.Bind();
		GL_Call(glUseProgram(shader_program_cube));    	 // Bind the required shader program to th OpenGL context

		if (translation_timer.IsTimerExpired()) 
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			// UPDATE THE ROTATION Z MATRIX AND PASS THE UPDATED ROTATION MATRIX TO THE VERTEX SHADER.
			++rotation_y;
			mat_rotation_y.SetRotation(rotation_y, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS); 
			SetUniformMat4f(shader_program_cube, u_rotation_y_mat.Get_Handle(), mat_rotation_y);

			translation_timer.Reset();
		}

		Render();									 // Render the scene

		window.SwapBuffers();

		window.PollEvents();
	}

	// Clean-up:
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
	GL_Call(glDeleteProgram(shader_program_cube));

	window.Exit();

    return 0;
}

void Render(void)
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	GL_ClearScreen(clear_color); // NEW: NOW CLEARS THE DEPTH BUFFER EACH FRAME => COMMENTED OUT

	GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

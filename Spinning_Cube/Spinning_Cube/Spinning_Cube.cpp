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

// TO DO: IF THE USER ALREADY SET A ROTATION MATRIX AND TRIES TO CHANGE THE AXIS OF THE SAME INSTANCE, RESET THE CURRENT ROTATION MATRIX BEFORE SETTING THE NEW VALUES!

void Render(void);

int main()
{
	Window window(800, 800, "Spinning cube"); // Square window: Aspect ration is not implemented yet

	// PROJECTION: COMMON PROJECTION MATRIX FOR ALL OBJECTS
	ProjectionMatrix4f projection_mat;
	projection_mat.SetFOV(90.0f);

	float floor_vertices[] =
	{
		//Position:		       Color:
		 0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 0. Top right
		-0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 1. Top left
		-0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 2. Bottom left
		 0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f  // 3. Bottom right
	};
	unsigned int floor_indices[] =	// Counter clockwise
	{
		0, 1, 2,			        // Top right, top left, bottom left
		2, 3, 0                     // Bottom left, bottom left, top right
	};

	GL_Vertex_Array vertex_array_floor;
	GL_VertexBuffer bufferV_floor(floor_vertices, 4 * 7 * sizeof(float));  // The vertex buffer is bound to the OpenGL context on instantiation
	GL_VertexBufferLayout layout_bufferV_floor;
	layout_bufferV_floor.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
	layout_bufferV_floor.Push<float>(4);								   // Push the amount of floats per vertex that are used for the vertex color
	vertex_array_floor.AddBuffer(bufferV_floor, layout_bufferV_floor);
	GL_ElementBuffer bufferE_floor(floor_indices, 2 * 3);				   // The element buffer is bound to the OpenGL contect on instantiation
	unsigned int shader_program_floor = CreateShaderProgram("../Resources/Shaders/Floor.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_floor);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// SCALING
	ScalingMatrix4f mat_scaling_floor;
	vec3f scaling_vec_floor = { 2.5f, 2.5f, 1.0f };
	mat_scaling_floor.SetScaling3f(scaling_vec_floor);
	// ROTATION
	RotationMatrix4f mat_rotation_x_floor;
	mat_rotation_x_floor.SetRotation(90.0f, GL_ROTATION_AXIS::GL_ROTATION_X_AXIS);
	// TRANSLATION
	TranslationMatrix4f mat_translation_floor;
	vec3f translation_vec_floor = { 0.0f, -0.75f, 2.5f };
	mat_translation_floor.SetTranslation3f(translation_vec_floor);
	// TRANSFORMATION
	Matrix4f mat_transformation_floor = mat_translation_floor * mat_rotation_x_floor * mat_scaling_floor;
	GL_Uniform u_transformation_mat_floor = GetUniform(shader_program_floor, "u_Transformation_mat");
	SetUniformMat4f(shader_program_floor, u_transformation_mat_floor.Get_Handle(), mat_transformation_floor);
	// PROJECTION
	GL_Uniform u_projection_mat_floor = GetUniform(shader_program_floor, "u_Projection_mat");
	SetUniformMat4f(shader_program_floor, u_projection_mat_floor.Get_Handle(), projection_mat);

	GL_Vertex_Array::Unbind();
	GL_VertexBuffer::Unbind();
	GL_ElementBuffer::Unbind();
	GL_Call(glUseProgram(0));



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

	
	GL_Vertex_Array vertex_array_cube;
	GL_VertexBuffer bufferV_cube(cube_vertices, 8 * 3 * sizeof(float));  // The vertex buffer is bound to the OpenGL context on instantiation
	GL_VertexBufferLayout layout_bufferV_cube;
	layout_bufferV_cube.Push<float>(3);									 // Push the amount of floats per vertex that are used for the vertex position
	// layout_bufferV_cube.Push<float>(4);									// Push the amount of floats per vertex that are used for the vertex color
	vertex_array_cube.AddBuffer(bufferV_cube, layout_bufferV_cube);
	GL_ElementBuffer bufferE_cube(cube_indices, 12 * 3);				 // The element buffer is bound to the OpenGL contect on instantiation

	unsigned int shader_program_cube = CreateShaderProgram("../Resources/Shaders/Cube.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_cube);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// SCALING
	ScalingMatrix4f mat_scaling_cube;
	vec3f scaling_vec_cube = { 1.0f, 1.0f, 1.0f };
	mat_scaling_cube.SetScaling3f(scaling_vec_cube);														  // Set the X, Y and Z scaling values in the translation matrix
	
	// ROTATION
	RotationMatrix4f mat_rotation_y_cube;
	// mat_rotation_y.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
	// mat_rotation_z.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);
	// mat_rotation_z.SetRotation(90.0f, GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS);

	// TRANSLATION
	TranslationMatrix4f mat_translation_cube;
	vec3f translation_vec_cube = { 0.0f, 0.0f, 2.5f };
	mat_translation_cube.SetTranslation3f(translation_vec_cube);											  // Set the X, Y and Z translation values in the translation matrix

	// TRANSFORMATION
	Matrix4f mat_transformation_cube = mat_translation_cube * mat_rotation_y_cube * mat_scaling_cube;
	GL_Uniform u_transformation_mat_cube = GetUniform(shader_program_cube, "u_Transformation_mat");
	SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), mat_transformation_cube);  // Pass the transformation matrix to the shader


	//// PROJECTION: COMMON PROJECTION MATRIX FOR ALL OBJECTS
	//ProjectionMatrix4f projection_mat;
	//projection_mat.SetFOV(90.0f);

	GL_Uniform u_projection_mat_cube = GetUniform(shader_program_cube, "u_Projection_mat");     // Pass the projection matrix to the shaders
	SetUniformMat4f(shader_program_cube, u_projection_mat_cube.Get_Handle(), projection_mat);   // IF THE CUBE IS NOT VISIBLE, TRANSLATE IT ALONG THE POSITIVE Z AXIS, THE CUBE WILL PROBABLY BE DEFINED IN CLIP SPACE COORDINATES [-1, 1] 
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


	
	// SET SCREEN CLEAR COLOR
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
	
	// RENDER LOOP 
	float rotation_y = 0.0f;
	Timer translation_timer(window.GetWindowTime(), 1/ 200.0); // FPS_60_PERIOD
	window.InitTime();

	while (!window.ShouldWindowClose())              // Loop until the user closes the window
	{
		window.UpdateTime();

		GL_Call(glClear(GL_COLOR_BUFFER_BIT));

		// RENDER THE FLOOR
		vertex_array_floor.Bind();
		GL_Call(glUseProgram(shader_program_floor));
		GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GL_Vertex_Array::Unbind();
		GL_Call(glUseProgram(0));


		// TRANSFORM AND RENDER THE CUBE:
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		vertex_array_cube.Bind();
		GL_Call(glUseProgram(shader_program_cube));    	 // Bind the required shader program to the OpenGL context

		if (translation_timer.IsTimerExpired()) 
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			// UPDATE THE ROTATION Z MATRIX AND PASS THE UPDATED ROTATION MATRIX TO THE VERTEX SHADER.
			++rotation_y;
			mat_rotation_y_cube.SetRotation(rotation_y, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			mat_transformation_cube = mat_translation_cube * mat_rotation_y_cube * mat_scaling_cube;			    // Calculate the transformation matrix again
			SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), mat_transformation_cube);  // Pass the transformation matrix to the shader

			translation_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		GL_Vertex_Array::Unbind();
		GL_Call(glUseProgram(0));

		// ORIGINAL
		// Render();									 // Render the scene

		window.SwapBuffers();

		window.PollEvents();
	}

	// Clean-up:
	bufferV_floor.Delete();
	bufferE_floor.Delete();
	vertex_array_floor.Delete();
	GL_Call(glDeleteProgram(shader_program_floor));

	bufferV_cube.Delete();
	bufferE_cube.Delete();
	vertex_array_cube.Delete();
	GL_Call(glDeleteProgram(shader_program_cube));

	window.Exit();

    return 0;
}

void Render(void) // TO DO: MOVE SETTING THE CLEARCOLOR, CLEARING AND RENDERING TO THE WINDOW CLASS ??
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F }; // TO DO: Setting the clear color is happening each call to Render() => This should only happen when a change in color needs to occur!
	GL_ClearScreen(clear_color); // NEW: NOW CLEARS THE DEPTH BUFFER EACH FRAME => COMMENTED OUT

	GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

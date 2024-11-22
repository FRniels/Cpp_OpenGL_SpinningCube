// See the Documentation folder in the repository for the explanation of the visual studio project configuration 
// to correctly include and link all necesarry files.

#include <iostream>

// The glew header must be included before any other opengl related files are included -> the glfw3.h includes gl.h !
#include "GL/glew.h"     // The glew header contains the function pointers to OpenGl functions
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Camera.h"
#include "GL_User_Types.h" 
#include "Math_Types.h"
#include "GL_ErrorHandeling.h"
#include "GL_ShaderProgram.h"
#include "GL_VertexArray.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"
#include "GL_Draw.h"
#include "Timer.h"

#include "Primitive_Shapes2D.h"
#include "Primitive_Shapes3D.h"

// TO DO: IF THE USER ALREADY SET A ROTATION MATRIX AND TRIES TO CHANGE THE AXIS OF THE SAME INSTANCE, RESET THE CURRENT ROTATION MATRIX BEFORE SETTING THE NEW VALUES!

void Render(void);

int main()
{
	Window window(1500, 800, "Spinning cube"); 

	Camera camera(90.0f, window.GetAspectRatio());

	// PROJECTION: COMMON PROJECTION MATRIX FOR ALL OBJECTS
	ProjectionMatrix4f projection_mat = camera.projection_mat; // TO DO: THIS IS JUST A QUICK TEST TO SEE IF THE ASPECT RATIO WORKS => ASPECT RATIO TESTED AND WORKS!


	Plane floor_plane;
	
	unsigned int shader_program_floor = CreateShaderProgram("../Resources/Shaders/Floor.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_floor);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// TRANSFORMATION
	floor_plane.transform.Scale(3.0f, 3.0f, 1.0f);
	floor_plane.transform.Rotate(90.0f, GL_ROTATION_AXIS::GL_ROTATION_X_AXIS);
	floor_plane.transform.Translate(0.0f, -0.75f, 2.5f);

	GL_Uniform u_transformation_mat_floor = GetUniform(shader_program_floor, "u_Transformation_mat");
	SetUniformMat4f(shader_program_floor, u_transformation_mat_floor.Get_Handle(), floor_plane.transform.GetTransformationMatrix());

	// PROJECTION
	GL_Uniform u_projection_mat_floor = GetUniform(shader_program_floor, "u_Projection_mat");
	SetUniformMat4f(shader_program_floor, u_projection_mat_floor.Get_Handle(), projection_mat);

	floor_plane.Unbind_AllBuffers();
	GL_Call(glUseProgram(0));



	Cube cube;

	unsigned int shader_program_cube = CreateShaderProgram("../Resources/Shaders/Cube.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_cube);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// TRANSFORMATION
	// cube.transform.Scale(1.0f, 1.0f, 1.0f);
	cube.transform.Translate(0.75f, 0.0f, 3.25f);

	GL_Uniform u_transformation_mat_cube = GetUniform(shader_program_cube, "u_Transformation_mat");
	SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), cube.transform.GetTransformationMatrix());

	// PROJECTION
	GL_Uniform u_projection_mat_cube = GetUniform(shader_program_cube, "u_Projection_mat");     // Pass the projection matrix to the shaders
	SetUniformMat4f(shader_program_cube, u_projection_mat_cube.Get_Handle(), projection_mat);   // IF THE CUBE IS NOT VISIBLE, TRANSLATE IT ALONG THE POSITIVE Z AXIS, THE CUBE WILL PROBABLY BE DEFINED IN CLIP SPACE COORDINATES [-1, 1] 
																					            // AND THUS BE TO CLOSE OR BEHIND THE 'CAMERA' AFTER PROJECTION																				   
	// FRAGMENT SHADER UNIFORMS:
	GL_Uniform u_window_height = GetUniform(shader_program_cube, "uWindow_Height");
	SetUniform1f(shader_program_cube, u_window_height.Get_Handle(), window.GetWindowHeight());

	cube.Unbind_AllBuffers();
	GL_Call(glUseProgram(0));



	Triangle_3D triangle_3d;

	unsigned int shader_program_triangle = CreateShaderProgram("../Resources/Shaders/Triangle.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_triangle);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// TRANSFORMATION
	// triangle_3d.transform.Scale(1.0f, 1.0f, 1.0f);	
	triangle_3d.transform.Translate(-0.75f, 0.0f, 1.75f);

	GL_Uniform u_transformation_mat_triangle = GetUniform(shader_program_triangle, "u_Transformation_mat");
	SetUniformMat4f(shader_program_triangle, u_transformation_mat_triangle.Get_Handle(), triangle_3d.transform.GetTransformationMatrix());

	// PROJECTION
	GL_Uniform u_projection_mat_triangle = GetUniform(shader_program_triangle, "u_Projection_mat");
	SetUniformMat4f(shader_program_triangle, u_projection_mat_triangle.Get_Handle(), projection_mat);

	// FRAGMENT SHADER UNIFORMS:
	GL_Uniform u_window_height_triangle = GetUniform(shader_program_triangle, "uWindow_Height");
	SetUniform1f(shader_program_triangle, u_window_height_triangle.Get_Handle(), window.GetWindowHeight());

	triangle_3d.Unbind_AllBuffers();
	GL_Call(glUseProgram(0));

	Pyramid pyramid;

	unsigned int shader_program_pyramid = CreateShaderProgram("../Resources/Shaders/Pyramid.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_pyramid);

	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// TRANSFORMATION
	// pyramid.transform.Scale(1.0f, 1.0f, 1.0f);
	pyramid.transform.Translate(0.75f, 0.0f, 1.75f);

	GL_Uniform u_transformation_mat_pyramid = GetUniform(shader_program_pyramid, "u_Transformation_mat");
	SetUniformMat4f(shader_program_pyramid, u_transformation_mat_pyramid.Get_Handle(), pyramid.transform.GetTransformationMatrix());

	// PROJECTION
	GL_Uniform u_projection_mat_pyramid = GetUniform(shader_program_pyramid, "u_Projection_mat");
	SetUniformMat4f(shader_program_pyramid, u_projection_mat_pyramid.Get_Handle(), projection_mat);

	// FRAGMENT SHADER UNIFORMS:
	GL_Uniform u_window_height_pyramid = GetUniform(shader_program_pyramid, "uWindow_Height");
	SetUniform1f(shader_program_pyramid, u_window_height_pyramid.Get_Handle(), window.GetWindowHeight());

	pyramid.Unbind_AllBuffers();
	GL_Call(glUseProgram(0));


	// FACE CULLING:
	// When having a closed mesh, avoid running the fragment shader on all fragments that are back facing the camera.
	// This to avoid unnecessary calculations and thus boost performance.
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// DEPTH TESTING		 // TO DO: RESEARCH DEPTH TEST => IF DEPTH TEST IS ENABLED, THE CUBE DISAPPEARS
	// Enable depth test     // THE DEPTH MUST BE CLEARED EACH FRAME => SEE THE RENDER FUNCTION FOR THE CHANGE IN CODE!
	// glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	// glDepthFunc(GL_LESS);


	
	// SET SCREEN CLEAR COLOR
	// vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	vec4f clear_color = { 0.2F, 0.2F, 0.2F, 0.0F };
	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
	
	// RENDER LOOP 
	float rotation_y_cube	    = 0.0f; 
	float rotation_y_triangle   = 0.0f;
	float rotation_y_pyramid    = 0.0f;
	float translation_y_Pyramid = 0.0f;
	Timer cube_timer(window.GetWindowTime(), 1/ 200.0); // FPS_60_PERIOD => CUBE TIMER
	Timer triangle_timer(window.GetWindowTime(), FPS_60_PERIOD);
	Timer pyramid_timer(window.GetWindowTime(), FPS_60_PERIOD);

	window.InitTime();

	while (!window.ShouldWindowClose())              // Loop until the user closes the window
	{
		window.UpdateTime();

		GL_Call(glClear(GL_COLOR_BUFFER_BIT));

		// RENDER THE FLOOR
		floor_plane.Bind();
		GL_Call(glUseProgram(shader_program_floor));
		// ORIGNAL ONE COLOR FLOOR PLANE
		// GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GL_Call(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr));   // TO DO: GET THE INDEX COUNT FROM THE ELEMENT BUFFER ITSELF THAT IS BEING DRAWN => THE DRAW CALLS SHOULD BE ABSTRACTED IN A RENDERER CLASS IN THE FUTURE!
		floor_plane.Unbind_VAO();
		GL_Call(glUseProgram(0));


		// TRANSFORM AND RENDER THE CUBE:
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		cube.Bind();
		GL_Call(glUseProgram(shader_program_cube));    	 // Bind the required shader program to the OpenGL context

		if (cube_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_cube;
			cube.transform.Rotate(rotation_y_cube, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), cube.transform.GetTransformationMatrix());

			cube_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		cube.Unbind_VAO();
		GL_Call(glUseProgram(0));


		// TRANSFORM AND RENDER THE TRIANGLE:
		triangle_3d.Bind();
		GL_Call(glUseProgram(shader_program_triangle));    	 // Bind the required shader program to the OpenGL context

		if (triangle_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_triangle;
			triangle_3d.transform.Rotate(rotation_y_triangle, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			SetUniformMat4f(shader_program_triangle, u_transformation_mat_triangle.Get_Handle(), triangle_3d.transform.GetTransformationMatrix());

			triangle_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		triangle_3d.Unbind_VAO();
		GL_Call(glUseProgram(0));

		// TRANSFORM AND RENDER THE PYRAMID:
		pyramid.Bind();
		GL_Call(glUseProgram(shader_program_pyramid));    	 // Bind the required shader program to the OpenGL context

		if (pyramid_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_pyramid;
			pyramid.transform.Rotate(rotation_y_pyramid, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);

			++translation_y_Pyramid;
			pyramid.transform.Translate(0.75f, (sin(TO_RADIANS(translation_y_Pyramid)) / 2.0f), 1.75f); // Translate the pyramid up and down over the Y-axis in the Y-range [-0.5, 0.5]

			SetUniformMat4f(shader_program_pyramid, u_transformation_mat_pyramid.Get_Handle(), pyramid.transform.GetTransformationMatrix());

			pyramid_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		pyramid.Unbind_VAO();
		GL_Call(glUseProgram(0));


		// ORIGINAL
		// Render();									 // Render the scene

		window.SwapBuffers();

		window.PollEvents();
	}

	// Clean-up:
	floor_plane.DeleteGLObjects();
	GL_Call(glDeleteProgram(shader_program_floor));

	cube.DeleteGLObjects();
	GL_Call(glDeleteProgram(shader_program_cube));

	triangle_3d.DeleteGLObjects();
	GL_Call(glDeleteProgram(shader_program_triangle));

	pyramid.DeleteGLObjects();
	GL_Call(glDeleteProgram(shader_program_pyramid));

	window.Exit();

    return 0;
}

void Render(void) // TO DO: MOVE SETTING THE CLEARCOLOR, CLEARING AND RENDERING TO THE WINDOW CLASS ??
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F }; // TO DO: Setting the clear color is happening each call to Render() => This should only happen when a change in color needs to occur!
	GL_ClearScreen(clear_color); // NEW: NOW CLEARS THE DEPTH BUFFER EACH FRAME => COMMENTED OUT

	GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

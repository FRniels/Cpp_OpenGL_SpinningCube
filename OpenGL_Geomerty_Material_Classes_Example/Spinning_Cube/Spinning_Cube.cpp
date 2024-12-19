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


	ShaderProgramManager shader_prog_manager;


	Plane floor_plane;
	vec3f floor_color = { 0.457f, 0.102f, 0.199f }; // THIS COLOR IS NOT USED AND SERVES ONLY TO PLEASE THE CURRENT SHADER IMPLEMENTATION. THE VERTICES INCLUDE COLOR DATA THAT IS USED INSIDE THE SHADER
	floor_plane.transform.Scale(3.0f, 3.0f, 1.0f);
	floor_plane.transform.Rotate(90.0f, GL_ROTATION_AXIS::GL_ROTATION_X_AXIS);
	floor_plane.transform.Translate(0.0f, -0.75f, 2.5f);
	
	// NOTE: THE SHADER CONSTRUCTOR RETRIEVES THE SHADER HANDLE BY NAME AND SETS THE UNIFORM TO THE PASSED VALUES, THIS MEANS THAT THE SHADER PROGRAM NEEDS TO BE BOUND 
	//       BY CALLING UseShaderProgram() BEFORE CREATING A SHADER INSTANCE!
	//       THE REQUIRED UNIFORM VALUES CAN BE SET BEFORE OR AFTER CREATING THE SHADER INSTANCE, BUT A DEFAULT VALUE NEEDS TO BE PROVIDED!
	unsigned int floor_vert_shader = shader_prog_manager.CreateShader(GL_VERTEX_SHADER, "../Resources/Shaders/Floor.vert");
	unsigned int floor_frag_shader = shader_prog_manager.CreateShader(GL_FRAGMENT_SHADER, "../Resources/Shaders/Floor.frag");
	unsigned int shader_program_floor_new = shader_prog_manager.CreateShaderProgram(floor_vert_shader, floor_frag_shader);
	shader_prog_manager.UseShaderProgram(shader_program_floor_new);
	Shader shader_floor(shader_program_floor_new, floor_plane.transform.GetTransformationMatrix(), projection_mat, window.GetWindowHeight(), floor_color);

	floor_plane.Unbind_AllBuffers();
	ShaderProgramManager::UnbindShaderProgam();



	Cube cube;
	vec3f cube_color = { 0.0f, 0.5f, 0.5f };
	cube.transform.Translate(0.75f, 0.0f, 3.25f);

	unsigned int shader_program_cube = shader_prog_manager.CreateShaderProgram("../Resources/Shaders/Cube.shader");
	shader_prog_manager.UseShaderProgram(shader_program_cube);
	Shader shader_cube(shader_program_cube, cube.transform.GetTransformationMatrix(), projection_mat, window.GetWindowHeight(), cube_color);

	cube.Unbind_AllBuffers();
	ShaderProgramManager::UnbindShaderProgam();



	Triangle_3D triangle_3d;
	vec3f triangle_color = { 0.0f, 0.5f, 0.5f };
	triangle_3d.transform.Translate(-0.75f, 0.0f, 1.75f);

	unsigned int shader_program_triangle = shader_prog_manager.CreateShaderProgram("../Resources/Shaders/Triangle.shader");  
	shader_prog_manager.UseShaderProgram(shader_program_triangle);
	Shader shader_triangle(shader_program_triangle, triangle_3d.transform.GetTransformationMatrix(), projection_mat, window.GetWindowHeight(), triangle_color);

	triangle_3d.Unbind_AllBuffers();
	ShaderProgramManager::UnbindShaderProgam();



	Pyramid pyramid;
	vec3f pyramid_color = { 0.0f, 0.5f, 0.5f };
	pyramid.transform.Translate(0.75f, 0.0f, 1.75f);

	unsigned int shader_program_pyramid = shader_prog_manager.CreateShaderProgram("../Resources/Shaders/Pyramid.shader"); 
	shader_prog_manager.UseShaderProgram(shader_program_pyramid);
	Shader shader_pyramid(shader_program_pyramid, pyramid.transform.GetTransformationMatrix(), projection_mat, window.GetWindowHeight(), pyramid_color);

	pyramid.Unbind_AllBuffers();
	ShaderProgramManager::UnbindShaderProgam();



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
		// shader_prog_manager.UseShaderProgram(shader_program_floor);
		shader_prog_manager.UseShaderProgram(shader_program_floor_new);
		// ORIGNAL ONE COLOR FLOOR PLANE
		// GL_Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		GL_Call(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr));   // TO DO: GET THE INDEX COUNT FROM THE ELEMENT BUFFER ITSELF THAT IS BEING DRAWN => THE DRAW CALLS SHOULD BE ABSTRACTED IN A RENDERER CLASS IN THE FUTURE!
		floor_plane.Unbind_VAO();
		ShaderProgramManager::UnbindShaderProgam();


		// TRANSFORM AND RENDER THE CUBE:
		// Bind the required/necesarry/application specific vao and shader program to the OpenGL context before drawing. => In this case, the vao and shader program stay the same thus is would be unnecessarry to perform these gl calls each iteration.
		cube.Bind();
		shader_prog_manager.UseShaderProgram(shader_program_cube);

		if (cube_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_cube;
			cube.transform.Rotate(rotation_y_cube, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			shader_cube.SetUniformMat4f(shader_cube.GetTransformationMatLoc(), cube.transform.GetTransformationMatrix());

			cube_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		cube.Unbind_VAO();
		ShaderProgramManager::UnbindShaderProgam();


		// TRANSFORM AND RENDER THE TRIANGLE:
		triangle_3d.Bind();
		shader_prog_manager.UseShaderProgram(shader_program_triangle);

		if (triangle_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_triangle;
			triangle_3d.transform.Rotate(rotation_y_triangle, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			shader_triangle.SetUniformMat4f(shader_triangle.GetTransformationMatLoc(), triangle_3d.transform.GetTransformationMatrix());

			triangle_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		triangle_3d.Unbind_VAO();
		ShaderProgramManager::UnbindShaderProgam();

		// TRANSFORM AND RENDER THE PYRAMID:
		pyramid.Bind();
		shader_prog_manager.UseShaderProgram(shader_program_pyramid);

		if (pyramid_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_pyramid;
			pyramid.transform.Rotate(rotation_y_pyramid, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);

			++translation_y_Pyramid;
			pyramid.transform.Translate(0.75f, (sin(TO_RADIANS(translation_y_Pyramid)) / 2.0f), 1.75f); // Translate the pyramid up and down over the Y-axis in the Y-range [-0.5, 0.5]
			shader_pyramid.SetUniformMat4f(shader_pyramid.GetTransformationMatLoc(), pyramid.transform.GetTransformationMatrix());

			pyramid_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		pyramid.Unbind_VAO();
		ShaderProgramManager::UnbindShaderProgam();


		// ORIGINAL
		// Render();									 // Render the scene

		window.SwapBuffers();

		window.PollEvents();
	}

	// Clean-up:
	floor_plane.DeleteGLObjects();
	// shader_prog_manager.DeleteShaderProgram(shader_program_floor);
	shader_prog_manager.DeleteShaderProgram(shader_program_floor_new);

	cube.DeleteGLObjects();
	shader_prog_manager.DeleteShaderProgram(shader_program_cube);

	triangle_3d.DeleteGLObjects();
	shader_prog_manager.DeleteShaderProgram(shader_program_triangle);

	pyramid.DeleteGLObjects();
	shader_prog_manager.DeleteShaderProgram(shader_program_pyramid);

	window.Exit();

    return 0;
}

void Render(void) // TO DO: MOVE SETTING THE CLEARCOLOR, CLEARING AND RENDERING TO THE WINDOW CLASS ??
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F }; // TO DO: Setting the clear color is happening each call to Render() => This should only happen when a change in color needs to occur!
	GL_ClearScreen(clear_color); // NEW: NOW CLEARS THE DEPTH BUFFER EACH FRAME => COMMENTED OUT

	GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

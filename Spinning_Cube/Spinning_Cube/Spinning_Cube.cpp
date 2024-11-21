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
	Window window(1500, 800, "Spinning cube"); // Square window: Aspect ration is not implemented yet

	Camera camera(90.0f, window.GetAspectRatio());

	// PROJECTION: COMMON PROJECTION MATRIX FOR ALL OBJECTS
	ProjectionMatrix4f projection_mat = camera.projection_mat; // TO DO: THIS IS JUST A QUICK TEST TO SEE IF THE ASPECT RATIO WORKS => ASPECT RATIO TESTED AND WORKS!


	Plane floor_plane;
	
	unsigned int shader_program_floor = CreateShaderProgram("../Resources/Shaders/Floor.shader"); // Create Shader Program 
	UseShaderProgram(shader_program_floor);

	// TO DO: ABSTRACT IN A CLASS TRANSFORM ???
	// SET SHADER UNIFORMS
	// VERTEX SHADER UNIFORMS:
	// SCALING
	ScalingMatrix4f mat_scaling_floor;
	vec3f scaling_vec_floor = { 3.0f, 3.0f, 1.0f };
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

	floor_plane.Unbind_AllBuffers();
	GL_Call(glUseProgram(0));



	Cube cube;

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
	vec3f translation_vec_cube = { 0.75f, 0.0f, 3.25f };
	mat_translation_cube.SetTranslation3f(translation_vec_cube);											  // Set the X, Y and Z translation values in the translation matrix

	// TRANSFORMATION
	Matrix4f mat_transformation_cube = mat_translation_cube * mat_rotation_y_cube * mat_scaling_cube;
	GL_Uniform u_transformation_mat_cube = GetUniform(shader_program_cube, "u_Transformation_mat");
	SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), mat_transformation_cube);    // Pass the transformation matrix to the shader

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
	// SCALING
	ScalingMatrix4f mat_scaling_triangle;
	vec3f scaling_vec_triangle = { 1.0f, 1.0f, 1.0f };
	mat_scaling_triangle.SetScaling3f(scaling_vec_triangle);

	// ROTATION
	RotationMatrix4f mat_rotation_y_triangle;
	// mat_rotation_y_triangle.SetRotation(0.0f, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
	
	// TRANSLATION
	TranslationMatrix4f mat_translation_triangle;
	vec3f translation_vec_triangle = { -0.75f, 0.0f, 1.75f };
	mat_translation_triangle.SetTranslation3f(translation_vec_triangle);

	// TRANSFORMATION
	Matrix4f mat_transformation_triangle = mat_translation_triangle * mat_rotation_y_triangle * mat_scaling_triangle;
	GL_Uniform u_transformation_mat_triangle = GetUniform(shader_program_triangle, "u_Transformation_mat");
	SetUniformMat4f(shader_program_triangle, u_transformation_mat_triangle.Get_Handle(), mat_transformation_triangle);

	// PROJECTION
	GL_Uniform u_projection_mat_triangle = GetUniform(shader_program_triangle, "u_Projection_mat");
	SetUniformMat4f(shader_program_triangle, u_projection_mat_triangle.Get_Handle(), projection_mat);

	// FRAGMENT SHADER UNIFORMS:
	GL_Uniform u_window_height_triangle = GetUniform(shader_program_triangle, "uWindow_Height");
	SetUniform1f(shader_program_triangle, u_window_height_triangle.Get_Handle(), window.GetWindowHeight());

	triangle_3d.Unbind_AllBuffers();
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
	// vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F };
	vec4f clear_color = { 0.2F, 0.2F, 0.2F, 0.0F };
	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
	
	// RENDER LOOP 
	float rotation_y = 0.0f; // CUBE
	float rotation_y_triangle = 0.0f;
	Timer translation_timer(window.GetWindowTime(), 1/ 200.0); // FPS_60_PERIOD => CUBE TIMER
	Timer triangle_timer(window.GetWindowTime(), FPS_60_PERIOD);

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

		if (translation_timer.IsTimerExpired()) 
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y;
			mat_rotation_y_cube.SetRotation(rotation_y, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			mat_transformation_cube = mat_translation_cube * mat_rotation_y_cube * mat_scaling_cube;			    // Calculate the transformation matrix again
			SetUniformMat4f(shader_program_cube, u_transformation_mat_cube.Get_Handle(), mat_transformation_cube);  // Pass the transformation matrix to the shader

			translation_timer.Reset();
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
			mat_rotation_y_triangle.SetRotation(rotation_y_triangle, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			mat_transformation_triangle = mat_translation_triangle * mat_rotation_y_triangle * mat_scaling_triangle;			// Calculate the transformation matrix again
			SetUniformMat4f(shader_program_triangle, u_transformation_mat_triangle.Get_Handle(), mat_transformation_triangle);  // Pass the transformation matrix to the shader

			triangle_timer.Reset();
		}

		GL_Call(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr)); // TO DO: RETRIEVE THE INDEX COUNT FROM THE ELEMENT BUFFER 
		triangle_3d.Unbind_VAO();
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

	window.Exit();

    return 0;
}

void Render(void) // TO DO: MOVE SETTING THE CLEARCOLOR, CLEARING AND RENDERING TO THE WINDOW CLASS ??
{
	vec4f clear_color = { 0.996F, 0.54F, 0.094F, 0.0F }; // TO DO: Setting the clear color is happening each call to Render() => This should only happen when a change in color needs to occur!
	GL_ClearScreen(clear_color); // NEW: NOW CLEARS THE DEPTH BUFFER EACH FRAME => COMMENTED OUT

	GL_Call(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // Draw the current bound vertex buffer using the indices specified in the element buffer
}

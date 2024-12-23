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

#include "Mesh.h"
#include "GL_Shaders.h"

#include "Renderer.h"
#include "Timer.h"


// TO DO: IF THE USER ALREADY SET A ROTATION MATRIX AND TRIES TO CHANGE THE AXIS OF THE SAME INSTANCE, RESET THE CURRENT ROTATION MATRIX BEFORE SETTING THE NEW VALUES!


int main()
{
	Window window(1500, 1200, "Spinning cube"); 

	vec4f clear_color = { 0.2F, 0.2F, 0.2F, 0.0F };
	Renderer renderer(clear_color);

	Camera camera(90.0f, 0.2f, 10.0f, window.GetAspectRatio(), renderer.context); // TO DO: SET THE NEAR AND FAR FIELD

	ShaderManager shader_manager;


	Geometry_Plane floor_geometry;
	vec4f floor_color = { 1.0f, 0.388f, 0.278f, 0.4f };
	Material floor_material(floor_color, shader_manager, "../Resources/Shaders/Floor.vert", "../Resources/Shaders/Floor.frag");
	Mesh floor_plane(&floor_geometry, &floor_material);
	floor_plane.transform.Scale(3.0f, 3.0f, 1.0f);
	floor_plane.transform.Rotate(90.0f, GL_ROTATION_AXIS::GL_ROTATION_X_AXIS);
	floor_plane.transform.Translate(0.0f, -0.75f, 2.5f);


	Geometry_Cube cube_geometry;
	vec4f cube_color = { 0.235f, 0.702f, 0.443f, 0.0f };
	Material cube_material(cube_color, window.GetWindowHeight(), shader_manager, "../Resources/Shaders/Cube.vert", "../Resources/Shaders/Cube.frag");
	Mesh cube_mesh(&cube_geometry, &cube_material);
	cube_mesh.transform.Translate(0.75f, 0.0f, 3.25f);


	Geometry_Triangle3D triangle_3d_geometry;
	vec4f triangle_color = { 0.416f, 0.353f, 0.804f, 0.0f };
	Material triangle_material(triangle_color, window.GetWindowHeight(), shader_manager, "../Resources/Shaders/Triangle.vert", "../Resources/Shaders/Triangle.frag");
	Mesh triangle_3d_mesh(&triangle_3d_geometry, &triangle_material);
	triangle_3d_mesh.transform.Translate(-0.75f, 0.0f, 1.75f);


	Geometry_Pyramid pyramid_geometry;
	vec4f pyramid_color = { 0.0f, 0.5f, 0.5f, 0.0f };
	Material pyramid_material(pyramid_color, window.GetWindowHeight(), shader_manager, "../Resources/Shaders/Pyramid.vert", "../Resources/Shaders/Pyramid.frag");
	Mesh pyramid_mesh(&pyramid_geometry, &pyramid_material);
	pyramid_mesh.transform.Translate(0.75f, 0.0f, 1.75f);


	std::vector<Mesh*> mesh_list;
	mesh_list.push_back(&floor_plane);
	mesh_list.push_back(&cube_mesh);
	mesh_list.push_back(&triangle_3d_mesh);
	mesh_list.push_back(&pyramid_mesh);


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

	
	// UPDATE / RENDER LOOP 
	float rotation_y_cube	    = 0.0f; 
	float rotation_y_triangle   = 0.0f;
	float rotation_y_pyramid    = 0.0f;
	float translation_y_Pyramid = 0.0f;
	Timer cube_timer(window.GetWindowTime(), 1/ 200.0); // FPS_60_PERIOD => CUBE TIMER
	Timer triangle_timer(window.GetWindowTime(), FPS_60_PERIOD);
	Timer pyramid_timer(window.GetWindowTime(), FPS_60_PERIOD);

	window.InitTime();

	// Loop until the user closes the window
	while (!window.ShouldWindowClose()) 
	{
		window.UpdateTime();

		// TRANSFORM THE CUBE:
		if (cube_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_cube;
			cube_mesh.transform.Rotate(rotation_y_cube, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			cube_timer.Reset();
		}


		// TRANSFORM THE TRIANGLE:
		if (triangle_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_triangle;
			triangle_3d_mesh.transform.Rotate(rotation_y_triangle, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);
			triangle_timer.Reset();
		}


		// TRANSFORM THE PYRAMID:
		if (pyramid_timer.IsTimerExpired())
		{
			// std::cout << "Translation timer expired. Reset timer." << std::endl;
			++rotation_y_pyramid;
			pyramid_mesh.transform.Rotate(rotation_y_pyramid, GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS);

			++translation_y_Pyramid;
			pyramid_mesh.transform.Translate(0.75f, (sin(TO_RADIANS(translation_y_Pyramid)) / 2.0f), 1.75f); // Translate the pyramid up and down over the Y-axis in the Y-range [-0.5, 0.5]

			pyramid_timer.Reset();
		}

		renderer.ClearScreen();
		renderer.Render(mesh_list, shader_manager);

		window.SwapBuffers();
		window.PollEvents();
	}

	// Clean-up:
	floor_plane.Delete(shader_manager);

	cube_mesh.Delete(shader_manager);

	triangle_3d_mesh.Delete(shader_manager); 

	pyramid_mesh.Delete(shader_manager);

	window.Exit();

    return 0;
}

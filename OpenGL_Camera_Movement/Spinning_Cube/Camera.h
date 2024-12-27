#ifndef CAMERA_H
#define CAMERA_H

#include <string.h>
#include "GL/glew.h" 
#include "GLFW/glfw3.h"
#include "Math_Types.h"
#include "Renderer.h"

// UVN Camera
class Camera 
{
public:

private:
	float FOV        =   0.0f;
	float near_field =   0.0f;
	float far_field  =   0.0f;
	vec3f position   = { 0.0f };

	ViewMatrix4f view_matrix; // Default identity matrix for now: UVN vectors are not set and thus aligned with the world XYZ for now! (this means no rotations of the camera)
	ProjectionMatrix4f projection_mat;

public:
	Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context);
	~Camera() {};

	inline void SetPosition(vec3f position) 
	{ 
		memcpy(this->position, position, sizeof(vec3f));
		view_matrix.SetWorldTranslation(position);
	}; 
	// void SetPosition(vec3f position);

	void UpdateProjectionMatrix(float FOV, float near_field, float far_field, float window_aspect_ratio);

	// Callback to register with the GLFW Key callback ( Set the callback using the window class method void SetKeyCallback(KeyCallback callback) )
	void Callback_Key(int key, int scancode, int action, int mods);
};

#endif // CAMERA_H

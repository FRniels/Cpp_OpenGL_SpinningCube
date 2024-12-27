#ifndef CAMERA_H
#define CAMERA_H

#include <string.h>
#include "Math_Types.h"
#include "Renderer.h"

// UVN Camera
class Camera 
{
public:

private:
	float FOV        = 0.0f;
	float near_field = 0.0f;
	float far_field  = 0.0f;
	vec3f position = { 0.0f };

	ViewMatrix4f view_matrix; // Default identity matrix for now: UVN vectors are not set and thus aligned with XYZ for now! (this means no rotations of the camera)
	ProjectionMatrix4f projection_mat;

public:
	Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context);
	~Camera() {};

	inline void SetPosition(vec3f position) { memcmp(this->position, position, 3 * sizeof(float)); }; // TO DO: ADJUST THE VIEW MATRIX

	void UpdateProjectionMatrix(float FOV, float near_field, float far_field, float window_aspect_ratio);
};

#endif // CAMERA_H

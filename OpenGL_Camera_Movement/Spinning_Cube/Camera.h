#ifndef CAMERA_H
#define CAMERA_H

#include "Math_Types.h"
#include "Renderer.h"

class Camera
{
public:

private:
	float FOV        = 0.0f;
	float near_field = 0.0f;
	float far_field  = 0.0f;
	ProjectionMatrix4f projection_mat;

public:
	Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context);
	~Camera() {};

	void UpdateProjectionMatrix(float FOV, float near_field, float far_field, float window_aspect_ratio);
};

#endif // CAMERA_H

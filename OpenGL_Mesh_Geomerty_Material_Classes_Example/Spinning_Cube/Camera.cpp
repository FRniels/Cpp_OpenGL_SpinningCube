#include "Camera.h"

Camera::Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context) : FOV(FOV)
{
	UpdateProjectionMatrix(FOV, window_aspect_ratio);
	render_context.matrix_projection = &projection_mat;
}

void Camera::UpdateProjectionMatrix(float FOV, float window_aspect_ratio)
{
	projection_mat.SetProjectionMatrix(FOV, window_aspect_ratio);
}

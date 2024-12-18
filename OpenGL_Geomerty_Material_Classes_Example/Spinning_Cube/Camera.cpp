#include "Camera.h"

Camera::Camera(float FOV, float window_aspect_ratio) : FOV(FOV)
{
	SetFOV(FOV, window_aspect_ratio);
}

void Camera::SetFOV(float FOV, float window_aspect_ratio)
{
	projection_mat.SetProjectionMatrix(FOV, window_aspect_ratio);
}

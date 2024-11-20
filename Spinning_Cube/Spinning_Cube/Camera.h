#ifndef CAMERA_H
#define CAMERA_H

#include "Math_Types.h"

class Camera
{
private:
	float FOV;
	ProjectionMatrix4f projection_mat;

public:
	Camera(float FOV, float window_aspect_ratio);
	~Camera() {};

	void SetFOV(float FOV, float window_aspect_ratio);
};

#endif // CAMERA_H

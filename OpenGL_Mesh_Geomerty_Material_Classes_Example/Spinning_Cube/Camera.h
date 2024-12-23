#ifndef CAMERA_H
#define CAMERA_H

#include "Math_Types.h"
#include "Renderer.h"

class Camera
{
public:
	// TO DO: THIS A JUST TO BE ABLE TO ACCESS THE PROJ MAT FROM MAIN TO TEST IF THE ASPECT RATIO WORKS
	//        IF THE TEST SUCCEEDS, MAKE IT PRIVATE AGAIN! => ASPECT RATIO TESTED AND WORKS!
	ProjectionMatrix4f projection_mat; 

private:
	float FOV;
	// ProjectionMatrix4f projection_mat;

public:
	Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context);
	~Camera() {};

	void UpdateProjectionMatrix(float FOV, float window_aspect_ratio);
};

#endif // CAMERA_H

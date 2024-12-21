#ifndef RENDERER_H
#define RENDERER_H

#include "Math_Types.h"

struct RenderContext 
{
	Matrix4f& matrix_transformation; // matrix_model
	Matrix4f& matrix_view;
	Matrix4f& matrix_projection;
};

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}
};

#endif // RENDERER_H
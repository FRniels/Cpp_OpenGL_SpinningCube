#ifndef RENDERER_H
#define RENDERER_H

#include "Math_Types.h"
#include "Mesh.h"
#include "GL_Shaders.h"
#include "GL_ErrorHandeling.h"

struct RenderContext 
{
	Matrix4f* matrix_transformation; // matrix_model
	Matrix4f* matrix_view;
	Matrix4f* matrix_projection;
};

class Renderer
{
private:
	// RenderContext context;

public:
	RenderContext context = { 0 };

	Renderer() {}
	~Renderer() {}

	void Render(Mesh& mesh, ShaderManager& shader_manager) const;
};

#endif // RENDERER_H
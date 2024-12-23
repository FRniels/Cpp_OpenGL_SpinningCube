#ifndef RENDERER_H
#define RENDERER_H

#include <string.h>
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
	vec4f clear_color     = { 0.2F, 0.2F, 0.2F, 0.0F };

	Renderer(vec4f clear_color)
	{
		memcpy(this->clear_color, clear_color, sizeof(vec4f));
		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
	}
	~Renderer() {}

	inline void ClearScreen() { GL_Call(glClear(GL_COLOR_BUFFER_BIT)); }
	void Render(Mesh& mesh, ShaderManager& shader_manager) const;
	void Render(std::vector<Mesh*>& mesh_list, ShaderManager& shader_manager) const;
};

#endif // RENDERER_H
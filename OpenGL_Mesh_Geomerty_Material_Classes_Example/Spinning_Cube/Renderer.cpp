#include "Renderer.h"

void Renderer::Render(Mesh& mesh, ShaderManager& shader_manager) const
{
	GL_Uniform_Handle_t shader_progam = shader_manager.GetActiveProgam();
	ASSERT(shader_progam != -1);

	// TO DO: SAVE THE UNIFORM LOCATIONS OR DIRECTLY SET THE UNIFORMS BY NAME
	GL_Uniform_Handle_t u_transformation_mat_loc = shader_manager.GetUniformByName(shader_progam, "u_Transformation_mat");
	shader_manager.SetUniformMat4f(u_transformation_mat_loc, mesh.transform.GetTransformationMatrix());

	GL_Uniform_Handle_t u_projection_mat_loc = shader_manager.GetUniformByName(shader_progam, "u_Projection_mat");
	shader_manager.SetUniformMat4f(u_projection_mat_loc, context.matrix_projection);

	GL_Call(glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
}

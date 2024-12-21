#include "Material.h"

Material::Material(const ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src)
{
	vert_shader    = shader_manager.CreateShader(GL_VERTEX_SHADER, "../Resources/Shaders/Floor.vert");
	frag_shader    = shader_manager.CreateShader(GL_FRAGMENT_SHADER, "../Resources/Shaders/Floor.frag");
	shader_program = shader_manager.CreateShaderProgram(vert_shader, frag_shader);

	shader_manager.UseShaderProgram(shader_program);
}
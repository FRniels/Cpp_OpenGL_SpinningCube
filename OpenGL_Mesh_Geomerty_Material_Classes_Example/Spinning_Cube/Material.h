#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL_Shaders.h"
#include "GL_User_Types.h"

class Material
{
private:
	GL_Uniform_Handle_t vert_shader    = -1;
	GL_Uniform_Handle_t frag_shader    = -1;
	GL_Uniform_Handle_t shader_program = -1;

	vec4f color = { 1.0f, 1.0f, 1.0f, 0.0f };

	// ShaderProgram shader_program;

public:
	Material(const ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src);
	~Material() {}
};

#endif // MATERIAL_H
#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL_ShaderProgram.h"

class Material
{
private:
	GL_Uniform_Handle_t vert_shader    = -1;
	GL_Uniform_Handle_t frag_shader    = -1;
	GL_Uniform_Handle_t shader_program = -1;

public:
	Material() {}
	~Material() {}
};

#endif // MATERIAL_H
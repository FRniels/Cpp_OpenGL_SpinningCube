#ifndef GL_UNIFORM_H
#define GL_UNIFORM_H

#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"
#include "GL_User_Types.h"

struct GL_Uniform
{
private:
	unsigned int handle;

public:
	GL_Uniform(unsigned int handle) : handle(handle) {}
	unsigned int Get_Handle() { return handle;  }
};

GL_Uniform GetUniform(unsigned int shader_program, const std::string& u_Name);
// Uniform set function overloading:
void SetUniform1f(unsigned int shader_program, const std::string& u_Name, float data);
void SetUniform1f(unsigned int shader_program, unsigned int u_Location, float data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS) 
void SetUniform4f(unsigned int shader_program, const std::string& u_Name, vec4f data);
void SetUniform4f(unsigned int shader_program, unsigned int u_Location, vec4f data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS)

#endif; // GL_UNIFORM_H

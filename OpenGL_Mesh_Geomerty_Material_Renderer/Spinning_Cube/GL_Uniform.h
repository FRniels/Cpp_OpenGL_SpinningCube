#ifndef GL_Uniform_Handle_t_H
#define GL_Uniform_Handle_t_H

#include <iostream>
#include <string>

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"
#include "GL_User_Types.h"
#include "Math_Types.h"

typedef int GL_Uniform_Handle_t; // int type to be able to check if glGetUniformLocation returns -1

enum GL_Uniform_Handle_t_t
{
	U_FLOAT_t, U_VEC4F_t, U_MAT4f_t
};

//struct GL_Uniform_Handle_t
//{
//private:
//	unsigned int handle;
//
//public:
//	GL_Uniform_Handle_t() { handle = 0; }
//	GL_Uniform_Handle_t(unsigned int handle) : handle(handle) {}
//	unsigned int Get_Handle() const { return handle; }
//};

GL_Uniform_Handle_t GetUniform(unsigned int shader_program, const std::string& u_Name);

// Uniform set function overloading:
// void SetUniform1f(   unsigned int shader_program, const std::string& u_Name,     float			 data);
void SetUniform1f(   unsigned int shader_program, unsigned int       u_Location, float			 data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS) 
// void SetUniform4f(   unsigned int shader_program, const std::string& u_Name,     vec4f			 data);
void SetUniform4f(   unsigned int shader_program, unsigned int		 u_Location, vec4f           data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS)
// void SetUniformMat4f(unsigned int shader_program, const std::string& u_Name,     const Matrix4f& mat4f);
void SetUniformMat4f(unsigned int shader_program, unsigned int		 u_Location, const Matrix4f& mat4f);  // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS) 

#endif; // GL_Uniform_Handle_t_H

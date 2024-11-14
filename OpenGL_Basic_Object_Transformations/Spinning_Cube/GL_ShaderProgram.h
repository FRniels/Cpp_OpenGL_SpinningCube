#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

#include <string>

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"
#include "GL_User_Types.h"
#include "GL_Uniform.h"



struct ShaderProgramSource 
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filepPath);						   // Returns the vertex and/or fragment shader source code.

unsigned int CompileShader(unsigned int type, std::string& source);					   // Returns the OpenGL shader obj handle.

unsigned int CreateShaderProgram(const std::string& filepPath);						   // All shaders in 1 file: Pass the file path in which all shaders are found. Returns the OpenGL shader program handle.

void UseShaderProgram(unsigned int shader_program); 

GL_Uniform GetUniform(unsigned int shader_program, const std::string& u_Name);
// Uniform set function overloading:
void SetUniform1f(unsigned int shader_program, const std::string& u_Name, float data);
void SetUniform1f(unsigned int shader_program, unsigned int u_Location,   float data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS) 
void SetUniform4f(unsigned int shader_program, const std::string& u_Name, vec4f data); 
void SetUniform4f(unsigned int shader_program, unsigned int u_Location,   vec4f data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS)

#endif  // GL_SHADER_PROGRAM
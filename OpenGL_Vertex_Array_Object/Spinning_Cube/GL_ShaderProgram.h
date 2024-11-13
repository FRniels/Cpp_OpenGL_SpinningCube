#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

#include <string>
#include "GL_User_Types.h"



struct ShaderProgramSource 
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filepPath);						   // Returns the vertex and/or fragment shader source code.

unsigned int CompileShader(unsigned int type, std::string& source);					   // Returns the OpenGL shader obj handle.

unsigned int CreateShaderProgram(const std::string& filepPath);						   // All shaders in 1 file: Pass the file path in which all shaders are found. Returns the OpenGL shader program handle.

void UseShaderProgram(unsigned int shader_program); 

// Uniform set function overloading:
void SetUniform(unsigned int shader_program, const std::string& u_Name, float data);
void SetUniform(unsigned int shader_program, const std::string& u_Name, vec4f data); 
void SetUniform(unsigned int shader_program, unsigned int u_Location,   vec4f data);   // SHOULD BE FASTER TO SEARCH UNIFORMS BY HANDLE THAN BY NAME (GL DOCS) => NOT IMPLEMENTED

#endif  // GL_SHADER_PROGRAM
#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

#include <string>
#include "GL_User_Types.h"


// struct ShaderProgramSource;
struct ShaderProgramSource // Temporary declaration and implementation that have access to this struct from the main source file
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filepPath);								// Returns the vertex and/or fragment shader source code

unsigned int CompileShader(unsigned int type, std::string& source);							// Returns the OpenGL shader obj handle

unsigned int CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader);   // Returns the OpenGL shader program handle

void UseShaderProgram(unsigned int shader_program); 

void SetUniform_vec4(unsigned int shader_program, const std::string& u_Name, vec4 data); 

#endif  // GL_SHADER_PROGRAM
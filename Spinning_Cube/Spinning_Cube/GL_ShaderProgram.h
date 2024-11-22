#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

#include <string>

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"
#include "GL_User_Types.h"
#include "GL_Uniform.h"

class Shader
{
public:
	Shader() {}
	~Shader() {}
};

struct ShaderProgramSource 
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filepPath);						   // Returns the vertex and/or fragment shader source code.

unsigned int CompileShader(unsigned int type, std::string& source);					   // Returns the OpenGL shader obj handle.

unsigned int CreateShaderProgram(const std::string& filepPath);						   // All shaders in 1 file: Pass the file path in which all shaders are found. Returns the OpenGL shader program handle.

void UseShaderProgram(unsigned int shader_program); 

#endif  // GL_SHADER_PROGRAM
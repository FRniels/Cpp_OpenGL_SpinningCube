#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

#include <string>

// struct ShaderProgramSource;

struct ShaderProgramSource // Temporary declaration and implementation that have access to this struct from the main source file
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filepPath);


#endif  // GL_SHADER_PROGRAM
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

unsigned int CompileShader(unsigned int type, std::string& source);

unsigned int CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader);


#endif  // GL_SHADER_PROGRAM
#ifndef GL_SHADER_PROGRAM_H
#define GL_SHADER_PROGRAM_H

#include <string>
#include <unordered_map>
#include "GL/glew.h"
#include "GL_ErrorHandeling.h"
#include "GL_User_Types.h"
#include "GL_Uniform.h"

struct ShaderProgramSource 
{
	std::string VertexShader;
	std::string FragmentShader;
};


class ShaderManager
{
private:
	GL_Uniform_Handle_t active_program = -1;

public:
	ShaderManager() {}
	~ShaderManager() {}

	unsigned int CreateShader(unsigned int shader_type, const std::string& shader_src) const; // Pass the OpenGL type of the shader, and the shader source file.

	unsigned int CreateShaderProgram(const std::string& filepPath) const; // All shaders in 1 file: Pass the file path in which all shaders are found. Returns the OpenGL shader program handle.
	unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader) const;
	
	inline void UseShaderProgram(unsigned int shader_program) { GL_Call(glUseProgram(shader_program)); active_program = shader_program; }
	inline void UnbindShaderProgam() { GL_Call(glUseProgram(0)); active_program = -1;  }

	inline GL_Uniform_Handle_t GetActiveProgam() const { return active_program; }

	// The shader program needs to be bound to the GL context before querying!
	std::unordered_map<std::string, GL_Uniform_Handle_t> QueryUniforms() const; 

	GL_Uniform_Handle_t GetUniformByName(unsigned int shader_program_handle, const std::string& u_Name) const;
	void SetUniform1f(   GL_Uniform_Handle_t u_Location, float			 data)  const;
	void SetUniform4f(   GL_Uniform_Handle_t u_Location, vec4f           data)  const;
	void SetUniformMat4f(GL_Uniform_Handle_t u_Location, const Matrix4f& mat4f) const;
	void SetUniformMat4f(GL_Uniform_Handle_t u_Location, const Matrix4f* mat4f) const;

	void DeleteShader(unsigned int shader) const;
	void DeleteShaderProgram(unsigned int shader_program) const;

private:
	ShaderProgramSource ParseShader(const std::string& filepPath) const;		   // Returns the vertex and/or fragment shader source code.
	std::string ParseShader_NEW(const std::string& filepPath) const;			   // This parser only handles 1 shader type defined in 1 source file unlike the other parser which handles vertex and fragment shaders defined in 1 file.

	unsigned int CompileShader(unsigned int type, std::string& source) const;	   // Returns the OpenGL shader obj handle.
};

#endif  // GL_SHADER_PROGRAM_H
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


class ShaderProgramManager
{
public:
	ShaderProgramManager() {}
	~ShaderProgramManager() {}

	unsigned int CreateShaderProgram(const std::string& filepPath);		   // All shaders in 1 file: Pass the file path in which all shaders are found. Returns the OpenGL shader program handle.

	inline void UseShaderProgram(unsigned int shader_program) { GL_Call(glUseProgram(shader_program)); }

	static inline void UnbindShaderProgam() { GL_Call(glUseProgram(0)); }

	void DeleteShaderProgram(unsigned int shader_program);

private:
	ShaderProgramSource ParseShader(const std::string& filepPath);		   // Returns the vertex and/or fragment shader source code.

	unsigned int CompileShader(unsigned int type, std::string& source);	   // Returns the OpenGL shader obj handle.
};


class Shader
{
private:
	unsigned int handle = 0;

	// SHADER UNIFORMS ARE INITIALISED (HARCODED) INSIDE GL_ShaderProgram.cpp
	// NOTE: FOR NOW, EVERY SHADER HAS TO OBEY THIS UNIFORM LAYOUT. LATER FEATURE IS TO ALLOW FOR OBJECT SPECIFIC SHADER UNIFORM LAYOUTS
	static const std::string u_transformation_mat_name;
	GL_Uniform_Handle_t u_transformation_mat_loc = 0;

	static const std::string u_projection_mat_name;
	GL_Uniform_Handle_t u_projection_mat_loc = 0;

	static const std::string u_color_name;
	GL_Uniform_Handle_t u_color_vec4f_loc = 0;

	static const std::string u_window_height_name;
	GL_Uniform_Handle_t u_window_height_1f_loc = 0;

public:
	Shader(unsigned int program_handle) : handle(program_handle) {}
	Shader(unsigned int program_handle, const Matrix4f& trans_mat, const Matrix4f& proj_mat, float window_height, vec4f color); // NOT SURE IF THIS CONSTRUCTOR IS TO STAY, IN THE CASE FOR THIS STATIC SHADER UNIFORM LAYOUT IT COULD STAY
	~Shader() {}

	unsigned int GetHandle() const { return handle; }

	void SetUniform1f(   GL_Uniform_Handle_t u_Location, float			data);
	void SetUniform4f(   GL_Uniform_Handle_t u_Location, vec4f           data);
	void SetUniformMat4f(GL_Uniform_Handle_t u_Location, const Matrix4f& mat4f);

	// GETTERS: THE SHADER LAYOUT IS HARDCODED FOR NOW. DO THESE INLINE GETTERS ADD A OVERHEAD ???
	inline GL_Uniform_Handle_t GetTransformationMatLoc() const { return u_transformation_mat_loc; }
	inline GL_Uniform_Handle_t GetProjectionMatLoc()     const { return u_projection_mat_loc; }
	inline GL_Uniform_Handle_t GetColorLoc()             const { return u_color_vec4f_loc; }
	inline GL_Uniform_Handle_t GetWindowHeightLoc()      const { return u_window_height_1f_loc; }

private:
	GL_Uniform_Handle_t GetUniformByName(const std::string& u_Name) const;
};

#endif  // GL_SHADER_PROGRAM
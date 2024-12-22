#ifndef GL_SHADER_PROGRAM
#define GL_SHADER_PROGRAM

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


class ShaderProgram
{
private:
	unsigned int handle = 0;

	GL_Uniform_Handle_t vert_shader    = -1;
	GL_Uniform_Handle_t frag_shader    = -1;
	GL_Uniform_Handle_t shader_program = -1;

	// SHADER UNIFORMS ARE INITIALISED (HARCODED) INSIDE GL_Shaders.cpp
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
	ShaderProgram(unsigned int program_handle) : handle(program_handle) {}
	ShaderProgram(unsigned int program_handle, const Matrix4f& trans_mat, const Matrix4f& proj_mat, float window_height, vec4f color); // NOT SURE IF THIS CONSTRUCTOR IS TO STAY, IN THE CASE FOR THIS STATIC SHADER UNIFORM LAYOUT IT COULD STAY
	~ShaderProgram() {}

	unsigned int GetHandle() const { return handle; }

	// TO DO: THESE METHODS SHOULD BE REMOVED AS I THINK IT BELONGS MORE TO THE SHADER MANAGER THAN THE PROGRAM ITSELF. THIS CLASS SHOULD BE MORE OF A DATA STRUCT.
	void SetUniform1f(   GL_Uniform_Handle_t u_Location, float			data);
	void SetUniform4f(   GL_Uniform_Handle_t u_Location, vec4f           data);
	void SetUniformMat4f(GL_Uniform_Handle_t u_Location, const Matrix4f& mat4f);

	// GETTERS: THE SHADER LAYOUT IS HARDCODED FOR NOW. DO THESE INLINE GETTERS ADD A OVERHEAD ???
	inline GL_Uniform_Handle_t GetTransformationMatLoc() const { return u_transformation_mat_loc; }
	inline GL_Uniform_Handle_t GetProjectionMatLoc()     const { return u_projection_mat_loc; }
	inline GL_Uniform_Handle_t GetColorLoc()             const { return u_color_vec4f_loc; }
	inline GL_Uniform_Handle_t GetWindowHeightLoc()      const { return u_window_height_1f_loc; }

private:
	// TO DO: THIS METHOD SHOULD BE REMOVED AS I THINK IT BELONGS MORE TO THE SHADER MANAGER THAN THE PROGRAM ITSELF. THIS CLASS SHOULD BE MORE OF A DATA STRUCT.
	GL_Uniform_Handle_t GetUniformByName(const std::string& u_Name) const;
};

#endif  // GL_SHADER_PROGRAM
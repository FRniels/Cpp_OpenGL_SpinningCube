#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL_Shaders.h"
#include "GL_User_Types.h"
#include <unordered_map>

class Material
{
private:
	GL_Uniform_Handle_t shader_vert_handle    = -1;
	GL_Uniform_Handle_t shader_frag_handle    = -1;
	GL_Uniform_Handle_t shader_program_handle = -1;

	// LATER FEATURE: QUERY ALL AVAILABLE UNIFORMS ON RUNTIME
	// std::unordered_map<std::string, GL_Uniform_Handle_t> uniformLocations;

	static const std::string u_color;
	GL_Uniform_Handle_t u_color_vec4f_loc = -1;
	vec4f u_color_value = { 1.0f, 1.0f, 1.0f, 0.0f };

	static const std::string u_window_height;
	GL_Uniform_Handle_t u_window_height_loc = -1;
	float u_window_height_value = 0.0f; 

public:
	Material(vec4f color, ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src);
	Material(vec4f color, float window_height, ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src);
	~Material() {}

	inline GL_Uniform_Handle_t GetShaderProgramHandle() const { return shader_program_handle; }

	inline void Bind(ShaderManager& shader_manager) const { shader_manager.UseShaderProgram(shader_program_handle); }
	void Delete(ShaderManager& shader_manager);
};

#endif // MATERIAL_H
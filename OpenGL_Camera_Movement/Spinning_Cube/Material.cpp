#include "Material.h"
#include <string.h>

const std::string Material::u_color         = "u_color";
const std::string Material::u_window_height = "u_window_height";

Material::Material(vec4f color, ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src)
{
	memcpy(u_color_value, color, sizeof(vec4f));

	// Create the shader program
	shader_vert_handle    = shader_manager.CreateShader(GL_VERTEX_SHADER,   "../Resources/Shaders/Floor.vert");
	shader_frag_handle    = shader_manager.CreateShader(GL_FRAGMENT_SHADER, "../Resources/Shaders/Floor.frag");
	shader_program_handle = shader_manager.CreateShaderProgram(shader_vert_handle, shader_frag_handle);

	// Bind the shader to the GL context, get the required uniform locations to make later uniform searches more efficient than with using the string name,
	// set the uniform values and finally unbind the shader program from the GL context.
	Bind(shader_manager);

	// LATER FEATURE: QUERY ALL AVAILABLE UNIFORMS ON RUNTIME
	//std::unordered_map<std::string, GL_Uniform_Handle_t> uniform_locations = shader_manager.QueryUniforms(); 
	//std::unordered_map<std::string, GL_Uniform_Handle_t>::const_iterator iterator = uniform_locations.find(u_color);
	//if (iterator != uniform_locations.end())
	//{
	//	shader_manager.SetUniform4f(iterator->second, color);
	//}

	 u_color_vec4f_loc = shader_manager.GetUniformByName(shader_program_handle, u_color);
	 shader_manager.SetUniform4f(u_color_vec4f_loc, u_color_value);

	shader_manager.UnbindShaderProgam();
}

Material::Material(vec4f color, float window_height, ShaderManager& shader_manager, const std::string& vert_shader_src, const std::string& frag_shader_src)
{
	// Save the passed uniform values
	memcpy(u_color_value, color, sizeof(vec4f));
	u_window_height_value = window_height;

	// Create the shader program
	shader_vert_handle    = shader_manager.CreateShader(GL_VERTEX_SHADER,   "../Resources/Shaders/Floor.vert");
	shader_frag_handle    = shader_manager.CreateShader(GL_FRAGMENT_SHADER, "../Resources/Shaders/Floor.frag");
	shader_program_handle = shader_manager.CreateShaderProgram(shader_vert_handle, shader_frag_handle);

	// Bind the shader to the GL context, get the required uniform locations to make later uniform searches more efficient than with using the string name,
	// set the uniform values and finally unbind the shader program from the GL context.
	Bind(shader_manager);

	u_color_vec4f_loc = shader_manager.GetUniformByName(shader_program_handle, u_color);
	shader_manager.SetUniform4f(u_color_vec4f_loc, u_color_value);

	u_window_height_loc = shader_manager.GetUniformByName(shader_program_handle, u_window_height);
	shader_manager.SetUniform1f(u_window_height_loc, u_window_height_value);

	shader_manager.UnbindShaderProgam();
}

void Material::Delete(ShaderManager& shader_manager)
{
	shader_manager.DeleteShader(shader_vert_handle);
	shader_vert_handle = -1;

	shader_manager.DeleteShader(shader_frag_handle);
	shader_frag_handle = -1;

	shader_manager.DeleteShaderProgram(shader_program_handle);
	shader_program_handle = -1;
}

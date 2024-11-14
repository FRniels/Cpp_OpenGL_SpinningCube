#include "GL_Uniform.h"

GL_Uniform GetUniform(unsigned int shader_program, const std::string& u_Name)
{
	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation != -1);

	GL_Uniform uniform(uniformLocation);
	return uniform;
}

void SetUniform1f(unsigned int shader_program, const std::string& u_Name, float data)
{
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: " << data << std::endl;

	// Check if the uniform exists and set it's value if the uniform has a valid location
	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation != -1);
	GL_Call(glUniform1f(uniformLocation, data));
}

void SetUniform1f(unsigned int shader_program, unsigned int u_Location, float data)
{
	ASSERT(u_Location != -1);
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Location: " << u_Location << " Value: " << data << std::endl;
	GL_Call(glUniform1f(u_Location, data));
}

void SetUniform4f(unsigned int shader_program, const std::string& u_Name, vec4f data)
{
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: ";
	for (int i = 0; i < VEC4F_SIZE; ++i)
	{
		std::cout << *(data + i) << "F ";
	}
	std::cout << std::endl;

	// Check if the uniform exists and set it's value if the uniform has a valid location
	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation != -1);
	GL_Call(glUniform4f(uniformLocation, *data, *(data + 1), *(data + 2), *(data + 3))); // Set the shader position uniform value
}

void SetUniform4f(unsigned int shader_program, unsigned int u_Location, vec4f data)
{
	ASSERT(u_Location != -1);

	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Location: " << u_Location << " Value: ";
	for (int i = 0; i < VEC4F_SIZE; ++i)
	{
		std::cout << *(data + i) << "F ";
	}
	std::cout << std::endl;

	GL_Call(glUniform4f(u_Location, *data, *(data + 1), *(data + 2), *(data + 3)));
}
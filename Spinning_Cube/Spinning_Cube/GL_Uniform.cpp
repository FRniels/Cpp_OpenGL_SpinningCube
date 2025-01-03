#include "GL_Uniform.h"

GL_Uniform_Handle_t GetUniform(unsigned int shader_program, const std::string& u_Name)
{
	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation != -1);

	// GL_Uniform_Handle_t uniform(uniformLocation);
	// return uniform;
	return uniformLocation;
}

//void SetUniform1f(unsigned int shader_program, const std::string& u_Name, float data)
//{
//	// std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: " << data << std::endl;
//
//	// Check if the uniform exists and set it's value if the uniform has a valid location
//	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
//	ASSERT(uniformLocation != -1);
//	GL_Call(glUniform1f(uniformLocation, data));
//}

void SetUniform1f(unsigned int shader_program, unsigned int u_Location, float data)
{
	ASSERT(u_Location != -1);
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Location: " << u_Location << " Value: " << data << std::endl;
	GL_Call(glUniform1f(u_Location, data));
}

//void SetUniform4f(unsigned int shader_program, const std::string& u_Name, vec4f data)
//{
//	// std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: ";
//	for (int i = 0; i < VEC4F_SIZE; ++i)
//	{
//		std::cout << *(data + i) << "F ";
//	}
//	std::cout << std::endl;
//
//	// Check if the uniform exists and set it's value if the uniform has a valid location
//	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
//	ASSERT(uniformLocation != -1);
//	GL_Call(glUniform4f(uniformLocation, *data, *(data + 1), *(data + 2), *(data + 3))); 
//}

void SetUniform4f(unsigned int shader_program, unsigned int u_Location, vec4f data)
{
	ASSERT(u_Location != -1);

	// std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Location: " << u_Location << " Value: ";
	for (int i = 0; i < VEC4F_SIZE; ++i)
	{
		std::cout << *(data + i) << "F ";
	}
	std::cout << std::endl;

	GL_Call(glUniform4f(u_Location, *data, *(data + 1), *(data + 2), *(data + 3)));
}

//void SetUniformMat4f(unsigned int shader_program, const std::string& u_Name, const Matrix4f& mat4f)
//{
//	// std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << std::endl;
//	GL_Call(int uniformLocation = glGetUniformLocation(shader_program, u_Name.c_str()));
//	ASSERT(uniformLocation != -1);
//	GL_Call(glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, mat4f.GetMatrix())); // Row major matrix: transpose == GL_TRUE
//}

void SetUniformMat4f(unsigned int shader_program, unsigned int u_Location, const Matrix4f& mat4f)
{
	ASSERT(u_Location != -1);
	// std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Location: " << u_Location << std::endl;
	GL_Call(glUniformMatrix4fv(u_Location, 1, GL_TRUE, mat4f.GetMatrix())); 
}

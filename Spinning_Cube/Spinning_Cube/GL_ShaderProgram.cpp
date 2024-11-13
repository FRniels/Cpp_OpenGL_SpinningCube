#include "GL_ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"


ShaderProgramSource ParseShader(const std::string& filepPath)
{
	std::ifstream stream(filepPath);

	/* An enumerable class to set the state/mode to the kind of shader the while loop is parsing.
	   These types are used as the index for the string stream array (ss[]) */
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];            // An stream array to store both the vertex and fragment shader sources.
	ShaderType type = ShaderType::NONE; // Create a shaderType instance to keep track of which shader source is being parsed at a given time.

	if (stream)
	{
		// std::cout << "File path is okay and stream object is created." << std::endl;

		while (getline(stream, line))
		{
			if (strncmp(line.c_str(), "/*", 2) == 0)           // Start of a block comment on a new line starting with /*
			{
				do
				{
					if (line.find("*/") != std::string::npos)  // End of the block comment
					{
						break;
					}
				} while (getline(stream, line));
				// THERE IS NO CHECK TO SEE IF A BLOCK COMMENT OPENED WITH /* BUT NOT CLOSED WITH */ => ALL THE LINES AFTER /* WILL BE IGNORED.
				// Go to the next line, when the loop breaks due to finding the end of the block comment. 
				// A comment like this could be made: /*comment*/ // comment => the last comment would be automatically skipped so this is not a problem.
				// This does not allow for comments inside statements like if(i == 0 /* comment*/){} !
			}
			else if (strncmp(line.c_str(), "//", 2) != 0)      // If a line starts with a single comment with //, skip the line
			{
				if (line.find("#shader") != std::string::npos) // Check which kind of shader is following in the upcoming lines
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
						// std::cout << "Vertex shader found." << std::endl;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAGMENT;
						// std::cout << "Fragment shader found." << std::endl;
					}
				}
				else // Actual shader code is found
				{
					std::size_t comment_start_index = std::string::npos;
					
					if ((comment_start_index = line.find("//")) != std::string::npos)      // Remove a comment starting with // after a line of shader code
					{
						line = line.substr(0, (comment_start_index)); 
					}
					else if ((comment_start_index = line.find("/*")) != std::string::npos) // Remove a block comment starting with /* after a line of shader code
					{
						if (line.find("*/") != std::string::npos)                          // Check if the block comment is ending on the same line
						{
							line = line.substr(0, (comment_start_index));
						}
						else                                                               // Else check the next lines until reaching the end of the block comment, ending with */
						{
							line = line.substr(0, (comment_start_index));
							std::cout << line << std::endl;                                // Save the valid shader source code before the block comment starts with /*
							ss[(int)type] << line << "\n";
							while (getline(stream, line))
							{
								if (line.find("*/") != std::string::npos)                  // No checking if the end of a block comment */ eventually exist, if not, all lines after the opening /* will be ignored.
								{
									line = "";
									break;
								}
							}
						}
					}

					std::cout << line << std::endl;
					if (type != ShaderType::NONE) // When comments are placed before the actual shader code, the shader type is not yet set and is by default ShaderType::NONE = -1 which is an invalid array index!
					{
						ss[(int)type] << line << "\n";
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Failed to created a stream object. Check your file path." << std::endl;
	}

	stream.close();

	return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int type, std::string& source)
{
	GL_Call(unsigned int shader = glCreateShader(type));
	const char* src = source.c_str();
	GL_Call(glShaderSource(shader, 1, &src, nullptr));
	GL_Call(glCompileShader(shader));

	// Error handeling 
	int result;
	GL_Call(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (!result)
	{
		// Print the shader info log if the shader compilation failed
		int length;
		GL_Call(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)alloca(length * sizeof(char));
		GL_Call(glGetShaderInfoLog(shader, length, &length, message));

		std::cout << (type == GL_VERTEX_SHADER ? "Vertex shader " : "Fragment shader ") << " failed to compile!" << std::endl;
		std::cout << message << std::endl;
		GL_Call(glDeleteShader(shader));	// The shader failed to compile so it is safe to delete the shader resources.
		return 0;
	}

	return shader;
}

unsigned int CreateShaderProgram(const std::string& filepPath)
{
	ShaderProgramSource shaderProgramSources = ParseShader(filepPath);							  

	GL_Call(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, shaderProgramSources.VertexShader);         
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shaderProgramSources.FragmentShader);     

	// Bind both shaders to the OpenGL context and link them to form a shader program
	GL_Call(glAttachShader(program, vs));
	GL_Call(glAttachShader(program, fs));
	GL_Call(glLinkProgram(program));
	GL_Call(glValidateProgram(program));

	// Delete the shader resources after the program validation succeeds.
	GL_Call(glDeleteShader(vs));
	GL_Call(glDeleteShader(fs));

	return program;
}

void UseShaderProgram(unsigned int shader_program)
{
	GL_Call(glUseProgram(shader_program));
}

void SetUniform(unsigned int shader_program, const std::string& u_Name, float data)
{
	/*
	  Notes:
		- Before an uniform handle can be retrieved, the shader program in which the uniform is used needs to be bound to the OpenGL context!
		- Keep in mind that an uniform is removed by the compiler if you don't use it!
		  This will trigger the ASSERT(), so watch out for this because sometimes
		  you forget to remove an unused uniform or have one declared for later usage or another situation.
	*/
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: " << data << std::endl;

	// Check if the uniform exists and set it's value if the uniform has a valid location
	GL_Call(int uniformLocation_position = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation_position != -1);
	GL_Call(glUniform1f(uniformLocation_position, data));
}

void SetUniform(unsigned int shader_program, const std::string& u_Name, vec4f data)
{
	/*
	  Notes: 
	    - Before an uniform handle can be retrieved, the shader program in which the uniform is used needs to be bound to the OpenGL context!
		- Keep in mind that an uniform is removed by the compiler if you don't use it!
		  This will trigger the ASSERT(), so watch out for this because sometimes
	      you forget to remove an unused uniform or have one declared for later usage or another situation.
	*/

	// Print info about the uniform to be set
	std::cout << std::endl << "Set shader uniform:" << std::endl << "Shader program: " << shader_program << " u_Name: " << u_Name << " Value: ";
	for (int i = 0; i < VEC4F_SIZE; ++i)
	{
		std::cout << *(data + i) << "F ";
	}
	std::cout << std::endl;

	// Check if the uniform exists and set it's value if the uniform has a valid location
	GL_Call(int uniformLocation_position = glGetUniformLocation(shader_program, u_Name.c_str()));
	ASSERT(uniformLocation_position != -1);
	GL_Call(glUniform4f(uniformLocation_position, *data, *(data + 1), *(data + 2), *(data + 3))); // Set the shader position uniform value
}



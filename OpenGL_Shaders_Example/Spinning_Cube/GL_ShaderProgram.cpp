#include "GL_ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//struct ShaderProgramSource
//{
//	std::string VertexShader;
//	std::string FragmentShader;
//};

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
	std::stringstream ss[2];            // An array to store both the vertex and fragment shader sources.
	ShaderType type = ShaderType::NONE; // Create a shaderType instance to keep track of which shader source is being parsed at a given time.

	if (stream)
	{
		// std::cout << "File path is okay and stream object is created." << std::endl;

		while (getline(stream, line))
		{
			if (strncmp(line.c_str(), "//", 2) != 0) // Ignore comments starting on a new line that start with a //
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
						std::cout << "Vertex shader found." << std::endl;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAGMENT;
						std::cout << "Fragment shader found." << std::endl;
					}
				}
			}

		}
	}
	else
	{
		std::cout << "File path is not okay and stream object has failed to be created." << std::endl;
	}

	stream.close();

	return { " ", " " };
}

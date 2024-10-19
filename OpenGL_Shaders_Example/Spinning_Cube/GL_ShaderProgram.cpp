#include "GL_ShaderProgram.h"

#include <iostream>
#include <fstream>

//struct ShaderProgramSource
//{
//	std::string VertexShader;
//	std::string FragmentShader;
//};

ShaderProgramSource ParseShader(const std::string& filepPath)
{
	std::ifstream stream(filepPath);

	if (stream)
	{
		std::cout << "File path is okay and stream object is created." << std::endl;
	}
	else
	{
		std::cout << "File path is not okay and stream object has failed to be created." << std::endl;
	}

	stream.close();

	return { " ", " " };
}

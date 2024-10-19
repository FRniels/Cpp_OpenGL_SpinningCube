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
			else if (strncmp(line.c_str(), "//", 2) != 0)      // Start of a comment a new line starting with //
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
				}
			}
		}
	}
	else
	{
		std::cout << "Failed to created a stream object. Check your file path." << std::endl;
	}

	stream.close();

	return { " ", " " };
}

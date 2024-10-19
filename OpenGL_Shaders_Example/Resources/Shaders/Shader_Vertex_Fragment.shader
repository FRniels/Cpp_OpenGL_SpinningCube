// This shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, following and ending on a line of shader code, following a line of shader code and ending on a new line: /* */
// Note: 
//	this file is not a .cpp file, we want to use this as a text file and give it the extension .shader
//	You can also create a seperate file for each shader, but in this case both the vertex and fragment shader are written in 1 file and a parser is written for this file.
//	In case of seperate files, you could name your file extensions like .vertexShader or .fragmentShader, it really doesn't matter which
//	extension, but make sure this file is text and not code that is compiled like .cpp
//	#shader vertex/fragment is used in this parser to identify which shader is which.

/* block comment */

/* block
   comment */
   
/*
	block comment
*/

#shader vertex
#version 330 core

layout(location = 0) in vec4 position; /* A block comment on the same line as shader source code */

void main()      // A comment on the same line as shader source code
{
	gl_Position = position;
};

#shader fragment // Another comment that the shader parser will ignore
#version 330 core

out vec4 color; /* A
				   weird
				   block comment */

void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
};
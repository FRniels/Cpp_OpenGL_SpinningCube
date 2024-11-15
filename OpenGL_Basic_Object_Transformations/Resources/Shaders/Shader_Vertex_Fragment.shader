// The shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, beginning and ending on a line of shader code, following a line of shader code and ending on a new line: /* */
// Note: 
//	#shader vertex/fragment is used in this parser to identify which shader is which.

#shader vertex
#version 330 core

layout(location = 0) in vec3 position; 	// Changed the type to vec3 instead of the vec4 in the previous examples. With vec4, the default W value will be 0 and thus unuseful. 
uniform mat4 u_Translation_mat;

void main()      
{	
	// First set the W component of the incoming vertices to 1.0. Multipy each vertex vector with the translation matrix passed by the CPU code.
	// The multiplication order is important! 
	// Correct order:
	gl_Position = u_Translation_mat * vec4(position, 1.0);
	// Incorrect order:
	// gl_Position = vec4(position, 1.0) * u_Translation_mat; // Test this line of code to see the weird result that probably was not the expected result!
	
};

#shader fragment 
#version 330 core

out vec4 color;   
uniform float uWindow_Height = 0.0f;

void main()
{	
	float lerpValue = gl_FragCoord.y / uWindow_Height;      // Assign a color that is a linear interpolation of 2 colors based on the Y-coo of the specific fragment.
	
	color = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
};
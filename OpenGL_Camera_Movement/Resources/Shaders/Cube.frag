// The shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, beginning and ending on a line of shader code, following a line of shader code and ending on a new line: /* */

#version 330 core

out vec4 color;  

uniform float u_window_height = 0.0f;
uniform vec4  u_color = {1.0f, 1.0f, 1.0f, 0.0f};

void main()
{	     
	float lerpValue = gl_FragCoord.y / u_window_height;
	color = mix(vec4(0.2f, 0.2f, 0.2f, 1.0f), u_color, lerpValue);	// Assign a color that is a linear interpolation of 2 colors based on the Y-coo of the specific fragment.
};
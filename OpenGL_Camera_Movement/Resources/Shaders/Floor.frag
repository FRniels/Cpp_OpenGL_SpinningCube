// The shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, beginning and ending on a line of shader code, following a line of shader code and ending on a new line: /* */

#version 330 core

out vec4 color;  

uniform vec4  u_color = {1.0f, 1.0f, 1.0f, 0.0f};
uniform float u_window_height = 1.0f;

void main()
{	
    color   = u_color;
    color.x *= (u_window_height / u_window_height); // JUST TO DO SOMETHING WITH u_window_height SO THE COMPILER DOESN'T REMOVE THE UNIFORM
};

// The shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, beginning and ending on a line of shader code, following a line of shader code and ending on a new line: /* */

#version 330 core

layout(location = 0) in vec3 position; 	// Changed the type to vec3 instead of the vec4 in the previous examples. With vec4, the default W value will be 0 and thus unuseful.
layout(location = 1) in vec4 color;

out vec4 colorFromVertex;

uniform mat4 u_Transformation_mat;
uniform mat4 u_Projection_mat;
uniform vec4 u_color;

void main()      
{	
	vec4 transformed_vertex = u_Transformation_mat * vec4(position, 1.0);
	gl_Position = u_Projection_mat * transformed_vertex;						    // Project the transformed vertex
	
	float temp = u_color.x / u_color.x; // JUST TO DO SOMETHING WITH u_color SO THE COMPILER DOESN'T REMOVE THE UNIFORM
	colorFromVertex = color * temp;
};
// The shader parser can handle comments: 
// 	- Single comments: on new lines and single comments following a line of shader code: //
//  - Block comments:  on new lines, beginning and ending on a line of shader code, following a line of shader code and ending on a new line: /* */
// Note: 
//	#shader vertex/fragment is used in this parser to identify which shader is which.

#shader vertex
#version 330 core

layout(location = 0) in vec3 position; 	// Changed the type to vec3 instead of the vec4 in the previous examples. With vec4, the default W value will be 0 and thus unuseful.
layout(location = 1) in vec4 color;

out vec4 colorFromVertex;

uniform mat4 u_Scaling_mat; 
uniform mat4 u_RotationY_mat;
uniform mat4 u_Translation_mat;
uniform mat4 u_Projection_mat;

void main()      
{	
	
	// When for example the order of Translation and Rotation is reversed, the result will be that the rotated vertices will rotate around the center point with a radius of the translation value.
	// This could be a desired effect when it is done by intention!
	mat4 transformation_mat = u_Translation_mat * u_RotationY_mat * u_Scaling_mat;  // Multiply the seperate transformations together to form one transformation matrix 
	vec4 transformed_vertex = transformation_mat * vec4(position, 1.0);
	gl_Position = u_Projection_mat * transformed_vertex;						    // Project the transformed vertex
	
	colorFromVertex = color;
};

#shader fragment 
#version 330 core

out vec4 color;  
in  vec4 colorFromVertex;

// uniform float uWindow_Height = 0.0f;

void main()
{	
	// float lerpValue = gl_FragCoord.y / uWindow_Height;      // Assign a color that is a linear interpolation of 2 colors based on the Y-coo of the specific fragment.
	
	color = colorFromVertex;

	// color = mix(colorFromVertex, vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
	// color = mix(vec4(0.2f, 0.2f, 0.2f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), lerpValue);
};
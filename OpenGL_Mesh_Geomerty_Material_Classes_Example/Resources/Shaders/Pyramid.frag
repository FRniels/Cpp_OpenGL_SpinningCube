#version 330 core

out vec4 color;
in vec4 colorFromVertex;

// uniform float uWindow_Height = 0.0f;
uniform float u_window_height = 0.0f;

void main()
{	
	// float lerpValue = gl_FragCoord.y / uWindow_Height;      // Assign a color that is a linear interpolation of 2 colors based on the Y-coo of the specific fragment.
	
	// color = mix(vec4(0.2f, 0.2f, 0.2f, 1.0f), colorFromVertex, lerpValue);
	// // color = mix(vec4(0.2f, 0.2f, 0.2f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), lerpValue);

	float lerpValue = gl_FragCoord.y / u_window_height;
	color = mix(vec4(0.2f, 0.2f, 0.2f, 1.0f), colorFromVertex, lerpValue); // Assign a color that is a linear interpolation of 2 colors based on the Y-coo of the specific fragment.
};
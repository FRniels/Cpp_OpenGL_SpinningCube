#include "Math_Types.h"

// TRANSLATION
void TranslationMatrix4f::SetTranslation3f(vec3f translation_xyz)						// Set the X, Y and Z translation values in the matrix
{
	if (translation_xyz)
	{
		mat4f[0][3] = *(translation_xyz);		 // X
		mat4f[1][3] = *(translation_xyz + 1);    // Y
		mat4f[2][3] = *(translation_xyz + 2);    // Z
	}
}


// ROTATION
void RotationMatrix4f::SetRotation(float degrees, GL_ROTATION_AXIS rotation_axis)		// Set the X, Y and Z scaling values in the matrix
{
	switch (rotation_axis)
	{
	case GL_ROTATION_AXIS::GL_ROTATION_X_AXIS:
		SetRotationX(degrees);
		break;
	case GL_ROTATION_AXIS::GL_ROTATION_Y_AXIS:
		SetRotationY(degrees);
		break;
	case GL_ROTATION_AXIS::GL_ROTATION_Z_AXIS:
		SetRotationZ(degrees);
		break;
	}
}

void RotationMatrix4f::SetRotationX(float degrees)
{
	// TEST OF MACRO'S
	// std::cout << "180deg to rad: " << TO_RADIANS(180) << "rad, 360deg to rad: " << TO_RADIANS(360) << "rad" << std::endl;
	// std::cout << "PIrad to degree: " << TO_DEGREES(PI) << "deg, 1rad to degree: " << TO_DEGREES(1) << "deg" << std::endl;
	
	mat4f[1][1] = cos(TO_RADIANS(degrees));
	mat4f[1][2] = -sin(TO_RADIANS(degrees));
	mat4f[2][1] = sin(TO_RADIANS(degrees));
	mat4f[2][2] = cos(TO_RADIANS(degrees));
}

void RotationMatrix4f::SetRotationY(float degrees)
{
	mat4f[0][0] = cos(TO_RADIANS(degrees));
	mat4f[0][2] = -sin(TO_RADIANS(degrees));
	mat4f[2][0] = sin(TO_RADIANS(degrees));
	mat4f[2][2] = cos(TO_RADIANS(degrees));
}

void RotationMatrix4f::SetRotationZ(float degrees)
{
	mat4f[0][0] = cos(TO_RADIANS(degrees));
	mat4f[0][1] = -sin(TO_RADIANS(degrees));
	mat4f[1][0] = sin(TO_RADIANS(degrees));
	mat4f[1][1] = cos(TO_RADIANS(degrees));
}


// SCALING
void ScalingMatrix4f::SetScaling3f(vec3f scaling_xyz)									// Set the X, Y and Z scaling values in the matrix
{
	if (scaling_xyz)
	{
		mat4f[0][0] = *(scaling_xyz);		// X
		mat4f[1][1] = *(scaling_xyz + 1);	// Y
		mat4f[2][2] = *(scaling_xyz + 2);	// Z
	}
}

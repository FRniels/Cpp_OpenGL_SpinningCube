#include "Math_Types.h"

void TranslationMatrix4f::SetTranslation3f(vec3f translation_xyz)							 // Set the X, Y and Z translation values in the matrix
{
	if (translation_xyz)
	{
		mat4f[0][3] = *(translation_xyz);		 // X
		mat4f[1][3] = *(translation_xyz + 1);    // Y
		mat4f[2][3] = *(translation_xyz + 2);    // Z
	}
}

void RotationMatrix4f::SetRotation4f(float degrees, GL_ROTATION_AXIS rotation_axis)
{

}

void ScalingMatrix4f::SetScaling3f(vec3f scaling_xyz)										 // Set the X, Y and Z scaling values in the matrix
{
	if (scaling_xyz)
	{
		mat4f[0][0] = *(scaling_xyz);		// X
		mat4f[1][1] = *(scaling_xyz + 1);	// Y
		mat4f[2][2] = *(scaling_xyz + 2);	// Z
	}
}
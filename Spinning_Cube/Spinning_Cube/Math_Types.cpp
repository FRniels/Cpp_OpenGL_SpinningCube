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

	/*
	{
		1.0f, 0.0f, 0.0f, translate_x,
		0.0f, 1.0f, 0.0f, translate_y,
		0.0f, 0.0f, 1.0f, translate_z,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	*/
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

	/*
	{
		1.0f, 0.0f,     0.0f,      0.0f,
		0.0f, cos(rad), -sin(rad), 0.0f,
		0.0f, sin(rad), cos(rad),  0.0f,
		0.0f, 0.0f,     0.0f,      1.0f
	};
	*/
}

void RotationMatrix4f::SetRotationY(float degrees)
{
	mat4f[0][0] = cos(TO_RADIANS(degrees));
	mat4f[0][2] = -sin(TO_RADIANS(degrees));
	mat4f[2][0] = sin(TO_RADIANS(degrees));
	mat4f[2][2] = cos(TO_RADIANS(degrees));

	/*
	{
		cos(rad), 0.0f, -sin(rad), 0.0f,
		0.0f,     1.0f, 0.0f,      0.0f,
		sin(rad), 0.0f, cos(rad),  0.0f,
		0.0f,     0.0f, 0.0f,      1.0f
	};
	*/
}

void RotationMatrix4f::SetRotationZ(float degrees)
{
	mat4f[0][0] = cos(TO_RADIANS(degrees));
	mat4f[0][1] = -sin(TO_RADIANS(degrees));
	mat4f[1][0] = sin(TO_RADIANS(degrees));
	mat4f[1][1] = cos(TO_RADIANS(degrees));

	/*
	{
		cos(rad), -sin(rad), 0.0f, 0.0f,
		sin(rad), cos(rad),  0.0f, 0.0f,
		0.0f,     0.0f,      1.0f, 0.0f,
		0.0f,     0.0f,      0.0f, 1.0f
	};
	*/
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

	/*
	{
		scale_x, 0.0f,    0.0f,    0.0f,
		0.0f,    scale_Y, 0.0f,    0.0f,
		0.0f,    0.0f,    scale_Z, 0.0f,
		0.0f,    0.0f,    0.0f,    1.0f
	};
	*/
}

void ProjectionMatrix4f::SetFOV(float fov_degrees)
{
	FOV = fov_degrees;
	float tanHalfFOV_rad        = tanf(TO_RADIANS(fov_degrees / 2.0f));
	float reciprocal_tanHalfFOV = 1.0f / tanHalfFOV_rad;

	// TO DO: RESEARCH WHICH IS THE VERTICAL AND WHICH IS THE HORIZONTAL FOV
	mat4f[0][0] = reciprocal_tanHalfFOV;	
	mat4f[1][1] = reciprocal_tanHalfFOV;	
	// ADJUST THE FOLLOWING MATRIX VALUES:
	mat4f[3][2] = 1.0f;
	mat4f[3][3] = 0.0f;
	// THIS IS DONE SO THAT THE VALUE OF THE Z COMPONENT IS COPIED INTO THE W COMPONENT
	// WHEN THIS PROJECTION MATRIX IS MULTIPLIED WITH THE TRANSFORMATION MATRIX.

	/*
	{
		1/tan(tanHalfFOV), 0.0f,			  0.0f,    0.0f,
		0.0f,              1/tan(tanHalfFOV), 0.0f,    0.0f,
		0.0f,              0.0f,			  1.0f,    0.0f,
		0.0f,              0.0f,			  1.0f,    0.0f   // SETTING W TO 0.0f AND mat4f[3][2] TO 1.0F WILL CAUSE A COPY OF THE Z COMPONENT INTO THE W COMPONENT AFTER MULTIPLICATION
	};
	*/

	// MORE INFO: https://www.youtube.com/watch?v=LhQ85bPCAJ8&list=PLA0dXqQjCx0S04ntJKUftl6OaOgsiwHjA&index=14
}

// DECLARE THIS OPERATOR OVERLOADING INSIDE THE BASE CLASS! REMOVE THE TRANSFORMATION MATRIX CLASS BECAUSE IT DOESN'T ACTUALLY DO SOMETHING!
/*
inline Matrix4f TransformationMatrix4f::operator*(const Matrix4f& right_hand_side) // WHY CANT I ACCES THE MATRIX ARRAY MAT4F WITHOUT MAKING THIS CLASS A FRIEND OF THE BASE CLASS
{																				   // THIS CLASS IS A CHILD CLASS AND THE MATRIX ARRAY IS PROTECTED ????
	Matrix4f mat_result;

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			mat4f[i][j] = 
				mat4f[i][0] * right_hand_side.mat4f[0][j] +
				mat4f[i][1] * right_hand_side.mat4f[1][j] +
				mat4f[i][2] * right_hand_side.mat4f[2][j] +
				mat4f[i][3] * right_hand_side.mat4f[3][j];
		}
	}

	return mat_result;
}
*/

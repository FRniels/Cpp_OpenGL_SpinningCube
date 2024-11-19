#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <math.h>
#include "GL_User_Types.h"

#define PI 3.14159265359
#define TO_RADIANS(degrees) ((degrees) * (PI / 180))
#define TO_DEGREES(radians) ((radians) * (180 / PI)) 

// class TransformationMatrix4f;

class Matrix4f
{

// friend TransformationMatrix4f; // THIS NEEDS TO BE REMOVED AFTER THE TRANSFOMATION MATRIX IS REMOVED

protected:
	float mat4f[4][4] = { 0.0f };

public:
	Matrix4f(/*float m00, float m01, float m02, float m03,
			 float m10, float m11, float m12, float m13,
			 float m20, float m21, float m22, float m23,
			 float m30, float m31, float m32, float m33*/)
	{
		/*mat4f[0][0] = m00; mat4f[0][1] = m01; mat4f[0][2] = m02; mat4f[0][3] = m03;
		mat4f[1][0] = m00; mat4f[1][1] = m01; mat4f[1][2] = m02; mat4f[1][3] = m03;
		mat4f[2][0] = m00; mat4f[2][1] = m01; mat4f[2][2] = m02; mat4f[2][3] = m03;
		mat4f[3][0] = m00; mat4f[3][1] = m01; mat4f[3][2] = m02; mat4f[3][3] = m03*/;

		mat4f[0][0] = mat4f[1][1] = mat4f[2][2] = mat4f[3][3] = 1.0f; // Set the default unity matrix
	}

	~Matrix4f() {}

	const float* GetMatrix() const { return &mat4f[0][0]; }             // Return a const pointer with const a function so that the original pointer can't be changed and the contents of the matrix can't be changed.
	
	inline Matrix4f operator*(const Matrix4f& right_hand_side)
	{
		Matrix4f mat_result;

		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4; ++j)
			{
				mat_result.mat4f[i][j] =
					mat4f[i][0] * right_hand_side.mat4f[0][j] +
					mat4f[i][1] * right_hand_side.mat4f[1][j] +
					mat4f[i][2] * right_hand_side.mat4f[2][j] +
					mat4f[i][3] * right_hand_side.mat4f[3][j];
			}
		}

		return mat_result;
	}
};


class TranslationMatrix4f : public Matrix4f
{
public:
	// using Matrix4f::Matrix4f;											// The using statement simplifies typing all the parameters again to pass them to the base constructor. This tell the compiler to use the base class construcor (c++11 feature)
	/*
	TranslationMatrix4f(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) {}
	*/
	~TranslationMatrix4f() {}

	void SetTranslation3f(vec3f translation_xyz);
};

class RotationMatrix4f : public Matrix4f
{
public:
	// using Matrix4f::Matrix4f; 

	~RotationMatrix4f() {}

	void SetRotation(float degrees, GL_ROTATION_AXIS rotation_axis);	// The rotation axis needs to be known because this influences which values to set in the Matrix4f

private:
	void SetRotationX(float degrees);
	void SetRotationY(float degrees);
	void SetRotationZ(float degrees);
};

class ScalingMatrix4f : public Matrix4f
{
public:
	// using Matrix4f::Matrix4f; 

	~ScalingMatrix4f() {}

	void SetScaling3f(vec3f scaling_xyz);
};

/*
class TransformationMatrix4f : public Matrix4f	// This matrix is the matrix multiplication: TranslationMatrix4f * RotationMatrix4f * ScalingMatrix4f => The order of matrix multiplication is very important!
{
public:
	// using Matrix4f::Matrix4f; 

	~TransformationMatrix4f() {}

	// DECLARE THIS OPERATOR OVERLOADING INSIDE THE BASE CLASS! REMOVE THE TRANSFORMATION MATRIX CLASS BECAUSE IT DOESN'T ACTUALLY DO SOMETHING!
	// inline Matrix4f operator*(const Matrix4f& right_hand_side);
};
*/

class ProjectionMatrix4f : public Matrix4f		// This matrix needs to be multiplied with the FINAL transformation matrix to transform the vertices and achieve perspective projection (sense of depth by accounting for the z values of the vertices. 
{												// No transformations may be made on this projection matrix !!
private:
	float FOV = 0.0f; // Vertical and horizontal Field Of View. => Later feature: allow for a seperate Vertical and Horizontal FOV.

public:
	// using Matrix4f::Matrix4f;

	~ProjectionMatrix4f() {}

	void SetFOV(float fov_degrees);
};

#endif // MATH_TYPES_H
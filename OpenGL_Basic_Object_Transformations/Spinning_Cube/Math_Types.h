#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include "GL_User_Types.h"

class Matrix4f
{
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
};


class TranslationMatrix4f : public Matrix4f
{
public:
	using Matrix4f::Matrix4f;											// The using statement simplifies typing all the parameters again to pass them to the base constructor. This tell the compiler to use the base class construcor (c++11 feature)
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
	using Matrix4f::Matrix4f; 

	~RotationMatrix4f() {}

	void SetRotation4f(float degrees, GL_ROTATION_AXIS rotation_axis);	// The rotation axis needs to be known because this influences which values to set in the Matrix4f
};

class ScalingMatrix4f : public Matrix4f
{
public:
	using Matrix4f::Matrix4f; 

	~ScalingMatrix4f() {}

	void SetScaling3f(vec3f scaling_xyz);
};

class TransformationMatrix4f : public Matrix4f							// This matrix is the matrix multiplication: TranslationMatrix4f * RotationMatrix4f * ScalingMatrix4f => The order of matrix multiplication is very important!
{
public:
	using Matrix4f::Matrix4f; 

	~TransformationMatrix4f() {}
};

#endif // MATH_TYPES_H
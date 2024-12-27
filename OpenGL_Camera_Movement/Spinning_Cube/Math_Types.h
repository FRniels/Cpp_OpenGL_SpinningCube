#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <math.h>
#include "GL_User_Types.h"

#define PI 3.14159265359
#define TO_RADIANS(degrees) ((degrees) * (PI / 180))
#define TO_DEGREES(radians) ((radians) * (180 / PI)) 

// Identity matrix
class Matrix4f
{
protected:
	float mat4f[4][4] = { 0.0f };

public:
	Matrix4f()
	{
		mat4f[0][0] = mat4f[1][1] = mat4f[2][2] = mat4f[3][3] = 1.0f; // Set the default unity matrix
	}

	~Matrix4f() {}

	const float* GetMatrix() const { return &mat4f[0][0]; }       
	
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
	TranslationMatrix4f()  {}
	~TranslationMatrix4f() {}

	void SetTranslation3f(vec3f translation_xyz);
	
	void InvertMatrix() {};
};

class RotationMatrix4f : public Matrix4f
{
public:
	RotationMatrix4f()  {}
	~RotationMatrix4f() {}

	void SetRotation(float degrees, GL_ROTATION_AXIS rotation_axis);	// The rotation axis needs to be known because this influences which values to set in the Matrix4f

private:
	void SetRotationX(float degrees);
	void SetRotationY(float degrees);
	void SetRotationZ(float degrees);

	void InvertMatrix() {};
};

class ScalingMatrix4f : public Matrix4f
{
public:
	ScalingMatrix4f()  {}
	~ScalingMatrix4f() {}

	void SetScaling3f(vec3f scaling_xyz);
};

// Camera view matrix: Translates the world coordinates of every object to the reference of the camera view
class ViewMatrix4f : public Matrix4f
{
private:
	vec3f U = { 1.0f, 0.0, 0.0f }; // Aligned with the world X-axis by default
	vec3f V = { 0.0f, 1.0, 0.0f }; // Aligned with the world Y-axis by default
	vec3f N = { 0.0f, 0.0, 1.0f }; // Aligned with the world Z-axis by default

public:
	ViewMatrix4f()  
	{
		mat4f[0][0] = U[0]; mat4f[0][1] = U[1]; mat4f[0][2] = U[2];
		mat4f[1][0] = V[0]; mat4f[1][1] = V[1]; mat4f[1][2] = V[2];
		mat4f[2][0] = N[0]; mat4f[2][1] = N[1]; mat4f[2][2] = N[2];
	}

	~ViewMatrix4f() {}

	// THIS IMPLEMENTATION WORKS BECAUSE THERE IS NO ROTATION YET 
	// => TO DO: ADJUST THE IMPLEMENTATION WHEN THE ROTATION OF THE CAMERA IS ADDED!
	//           USE THE INVERSE METHOD OF THE TRANSLATION MATRIX.
	inline void SetWorldTranslation(vec3f translation_xyz)
	{
		mat4f[0][3] = -(*translation_xyz);       // -X
		mat4f[1][3] = -(*(translation_xyz + 1)); // -Y
		mat4f[2][3] = -(*(translation_xyz + 2)); // -Z
	}
};

class ProjectionMatrix4f : public Matrix4f		// This matrix needs to be multiplied with the FINAL transformation matrix to transform the vertices and achieve perspective projection (sense of depth by accounting for the z values of the vertices. 
{												// No transformations may be made on this projection matrix !!
private:
	// float FOV = 0.0f; // Vertical and horizontal Field Of View. => Later feature: allow for a seperate Vertical and Horizontal FOV.

public:
	ProjectionMatrix4f() {}
	~ProjectionMatrix4f() {}

	void SetProjectionMatrix(float fov_degrees, float near_field, float far_field, float aspect_ration);

private:
	void SetFOV(float fov_degrees);
	void SetNearFarField(float near_field, float far_field);
	void SetAspectRatio(float aspect_ration);
};

#endif // MATH_TYPES_H
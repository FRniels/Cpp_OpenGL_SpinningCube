#ifndef MATH_TYPES_H
#define MATH_TYPES_H

class Matrix4f
{
public:
	float mat4f[4][4];

public:
	Matrix4f(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		mat4f[0][0] = m00; mat4f[0][1] = m01; mat4f[0][2] = m02; mat4f[0][3] = m03;
		mat4f[1][0] = m00; mat4f[1][1] = m01; mat4f[1][2] = m02; mat4f[1][3] = m03;
		mat4f[2][0] = m00; mat4f[2][1] = m01; mat4f[2][2] = m02; mat4f[2][3] = m03;
		mat4f[3][0] = m00; mat4f[3][1] = m01; mat4f[3][2] = m02; mat4f[3][3] = m03;
	}

	~Matrix4f() {}
};


#endif // MATH_TYPES_H
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GL_User_Types.h"
#include "Math_Types.h"

// SAVING ALL TRANSFORMATION VECTORS, ROTATION ANGLE AND AXIS TO HAVE ACCESS TO THE OBJECT'S WORLD LOCATION

struct Transform // TO DO: STILL NEED TO ALLOW FOR ROTATING ON MORE THAN 1 AXIS !
{
private:
	vec3f				scaling_vec = { 1.0f, 1.0f, 1.0f };
	ScalingMatrix4f     mat_scaling;

	float			    rotation_degrees = 0.0f;
	GL_ROTATION_AXIS    rotation_axis;
	RotationMatrix4f    mat_rotation;
	 
	vec3f			    translation_vec = { 0.0f, 0.0f, 0.0f };
	TranslationMatrix4f mat_translation;

	Matrix4f            mat_transformation; 

public: 

	// NOTE: THE SEPERATE TRANSFORMATIONS RECALCULATE THE FINAL TRANSFORMATION MATRIX. 
	// IF NECESSARY FOR PERFORMANCE OR AN OTHER REASON, A SEPERATE METHOD COULD BE MADE TO FIRST SET ALL THE SEPERATE TRANSFORMATION MATRICES 
	// AND THEN CALCULATE THE FINAL TRANSFORMATION MATRIX.
	inline void Scale(float x, float y, float z) 
	{
		scaling_vec[0] = x;
		scaling_vec[1] = y;
		scaling_vec[2] = z;
		mat_scaling.SetScaling3f(scaling_vec);

		CalculateTransformationMatrix();
	}

	inline void Rotate(float degrees, GL_ROTATION_AXIS axis) 
	{
		rotation_degrees = degrees;
		rotation_axis = axis;
		mat_rotation.SetRotation(degrees, axis);

		CalculateTransformationMatrix();
	}

	inline void Translate(float x, float y, float z)
	{
		translation_vec[0] = x;
		translation_vec[1] = y;
		translation_vec[2] = z;
		mat_translation.SetTranslation3f(translation_vec);

		CalculateTransformationMatrix();
	}

	const Matrix4f& GetTransformationMatrix() { return mat_transformation; }

private:
	inline void CalculateTransformationMatrix() 
	{
		mat_transformation = mat_translation * mat_rotation * mat_scaling;
	}
};

#endif // TRANSFORM_H

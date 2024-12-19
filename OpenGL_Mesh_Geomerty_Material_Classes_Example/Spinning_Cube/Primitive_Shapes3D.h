#ifndef PRIMITIVE_SHAPES3D_H
#define PRIMITIVE_SHAPES3D_H

#include "Object.h"
#include "GL_VertexArray.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"

// NOTE: THESE CLASSES ARE MERELY A STARTING POINT. THE CUBE AND THE 3D TRIANGLE WILL BE HARDCODED FOR NOW INSTEAD OF DYNAMICALLY PROGRAMABLE

class Primitive_Shape3D : public Object
{
public:
	Primitive_Shape3D() {}
	~Primitive_Shape3D() {}

};


class Pyramid : public Primitive_Shape3D
{
private:
	float pyramid_vertices[35] =
	{
		// Position                Color
		  0.0f,   0.25f,   0.0f,   0.996f, 0.54f, 0.094f, 0.0f,  // 0. Top
		 0.25f,  -0.25f,  0.25f,   0.996f, 0.54f, 0.094f, 0.0f,  // 1. Back:  Bottom right
		-0.25f,  -0.25f,  0.25f,   0.996f, 0.54f, 0.094f, 0.0f,  // 2. Back:  Bottom left
		-0.25f,  -0.25f, -0.25f,   0.996f, 0.54f, 0.094f, 0.0f,  // 3. Front: Bottom left
		 0.25f,  -0.25f, -0.25f,   0.996f, 0.54f, 0.094f, 0.0f   // 4. Front: Bottom right
	};
	unsigned int pyramid_indices[18] = // Counter clockwise
	{
		// FRONT PLANE
		4, 0, 3,		  // Front Bottom right, Top,				 Front Bottom left
		// BACK PLANE
		2, 0, 1,		  // Back Bottom left,   Top,				 Back Bottom right
		// RIGHT PLANE
		1, 0, 4,		  // Back Bottom right,  Top,				 Front Bottom right
		// LEFT PLANE
		3, 0, 2,		  // Front Bottom left,  Top,                Back Bottom left
		// BOTTOM PLANE
		1, 4, 3,		  // Back Bottom right,  Front Bottom right, Front Bottom left
		3, 2, 1,		  // Front Bottom left,  Back Bottom left  , Back Bottom right
	};

public:
	Pyramid();
	~Pyramid() {}

	inline void Bind() { vertex_array.Bind(); } // TO DO: MAKE BIND A VIRTUAL METHOD OF BASE CLASS OBJECT ???? => WATCH OUT: THIS METHOD DOES NOT CHECK IF THE VERTEX ARRAY IS DELETED !!! => TO DO: FIX THIS!

private:
	void InitBuffers();
	void InitVAO();
};

#endif // PRIMITIVE_SHAPES3D_H

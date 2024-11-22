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

class Cube : public Primitive_Shape3D
{
private:
	// TO DO: ALL CUBE INSTANCES CAN USE THE SAME VERTICES AND INDICES SO THESE DATA ARRAYS SHOULD BE STATIC FOR ALL CUBE OBJECTS. ALL CHANGES IN TRANSFORMATIONS WILL HAPPEN WITH MATRIX MULTIPLICATION SO ALL CUBES CAN HAVE THE SAME LOCAL COORDINATES. => THIS CUBE EXAMPLE IS JUST A HARDCODED TEST OF THE OBJECT/SHAPES CLASS STRUCTURE
	float cube_vertices[24] =	   // BLENDER .ply EXPORT
	{
		-0.5f,  0.5f,  0.5f,   // 0. Back:  Top left
		 0.5f,  0.5f,  0.5f,   // 1. Back:  Top right
		 0.5f,  0.5f, -0.5f,   // 2. Front: Top right
		-0.5f,  0.5f, -0.5f,   // 3. Front: Top left
		-0.5f, -0.5f, -0.5f,   // 4. Front: Bottom left
		 0.5f, -0.5f, -0.5f,   // 5. Front: Bottom right
		 0.5f, -0.5f,  0.5f,   // 6. Back:  Bottom right
		-0.5f, -0.5f,  0.5f    // 7. Back:  Bottom left
	};
	unsigned int cube_indices[36] = // Counter clockwise		
	{
		// BLENDER EXPORT: Fails to render, except for 1 triangle => 4, 0, 1 doesn't make any sense to me ???
		/*4, 0, 1, 2, 3,
		4, 4, 3, 2, 5,
		4, 5, 2, 1, 6,
		4, 6, 7, 4, 5,
		4, 7, 0, 3, 4,
		4, 6, 1, 0, 7*/

		// Cube order explanation: https://stackoverflow.com/questions/8142388/in-what-order-should-i-send-my-vertices-to-opengl-for-culling
		// FRONT FACE:
		// TRIANGLE 1:
		1, 0, 7,       // Back Top right, Back top left, Back bottom left
		// TRIANGLE 2:
		7, 6, 1,       // Back bottom left, Back bottom right, Back top right

		// BACK FACE:
		// TRIANGLE 1:
		2, 5, 4,       // Front Top right, Front botom right, Front bottom left
		// TRIANGLE 2:
		4, 3, 2,       // Front bottom left, Front top left, Front top right

		// TOP FACE:
		// TRIANGLE 1:
		2, 3, 0,       // Front top right, Front top left, Back top left
		// TRIANGLE 2:
		0, 1, 2,       // Back top left, Back top right, Front top right

		// BOTTOM FACE: 
		// TRIANGLE 1:
		6, 7, 4,       // Back bottom right, Back bottom left, Front bottom left
		// TRIANGLE 2:
		4, 5, 6,       // Front bottom left, Front bottom right, Back bottom right

		// RIGHT FACE:
		// TRIANGLE 1:
		2, 1, 6,       // Front top right, Back top right, Back bottom right
		// 6, 1, 2,
		// TRIANGLE 2:
		6, 5, 2,       // Back bottom right, Front bottom right, Front top right
		// 2, 5, 6,

		// LEFT FACE:
		// TRIANGLE 1:
		0, 3, 4,	   // Back top left, Front top left, Front bottom left
		// TRIANGLE 2:
		4, 7, 0        // Front bottom left, Back bottom left, Back top left
	};

public:
	Cube();
	~Cube() {}
	 
	inline void Bind() { vertex_array.Bind(); } // TO DO: MAKE BIND A VIRTUAL METHOD OF BASE CLASS OBJECT ???? => WATCH OUT: THIS METHOD DOES NOT CHECK IF THE VERTEX ARRAY IS DELETED !!! => TO DO: FIX THIS!

private:
	void InitBuffers();
	void InitVAO();
};

class Triangle_3D : public Primitive_Shape3D
{
private:
	float triangle_vertices[18] =
	{
		 0.0f,  0.5f,  0.1f,   // 0. Back:  Top
		 0.5f, -0.5f,  0.1f,   // 1. Back:  Bottom right
		-0.5f, -0.5f,  0.1f,   // 2. Back:  Bottom left
		 0.0f,  0.5f, -0.1f,   // 3. Front: Top
		-0.5f, -0.5f, -0.1f,   // 4. Front: Bottom left
		 0.5f, -0.5f, -0.1f    // 5. Front: Bottom right
	};
	unsigned int triangle_indices[24] = // Counter clockwise		
	{
		// Front face
		3, 4, 5,       // Front top,         Front bottom left,  Front bottom right
		// Back face
		0, 1, 2,       // Back top,          Back bottom left,   Back bottom right
		// Bottom face
		1, 5, 4,       // Back Bottom right, Front Bottom right, Front Bottom left
		4, 2, 1,       // Front Bottom left, Back Bottom left,   Back Bottom right
		// Left face
		4, 3, 0,       // Front bottom left, Front top,          Back top
		0, 2, 4,       // Back top         , Back bottom left,   Front bottom left
		// Right face
		1, 0, 3,       // Back bottom right, Back top,           Front top
		3, 5, 1        // Front top,         Front bottom right, Back bottom right
	};

public:
	Triangle_3D();
	~Triangle_3D() {}

	inline void Bind() { vertex_array.Bind(); } // TO DO: MAKE BIND A VIRTUAL METHOD OF BASE CLASS OBJECT ???? => WATCH OUT: THIS METHOD DOES NOT CHECK IF THE VERTEX ARRAY IS DELETED !!! => TO DO: FIX THIS!

private:
	void InitBuffers();
	void InitVAO();
};

#endif // PRIMITIVE_SHAPES3D_H

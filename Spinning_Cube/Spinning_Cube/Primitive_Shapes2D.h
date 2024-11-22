#ifndef PRIMITIVE_SHAPES2D_H
#define PRIMITIVE_SHAPES2D_H

#include "Object.h"

// NOTE: THESE CLASSES ARE MERELY A STARTING POINT. THE FLOOR PLAIN WILL BE HARDCODED FOR NOW INSTEAD OF A DYNAMICALLY PROGRAMABLE

class Primitive_Shape2D : public Object
{

public:
	Primitive_Shape2D() {}
	~Primitive_Shape2D() {}

};

class Plane : public Primitive_Shape2D
{
private:
	// TO DO: ALL PLANE INSTANCES CAN USE THE SAME VERTICES AND INDICE SO THESE DATA ARRAYS SHOULD BE STATIC FOR ALL PLANE OBJECTS. ALL CHANGES IN TRANSFORMATIONS WILL HAPPEN WITH MATRIX MULTIPLICATION SO ALL PLANES CAN HAVE THE SAME LOCAL COORDINATES. => THIS FLOOR EXAMPLE IS JUST A HARDCODED TEST OF THE OBJECT/SHAPES CLASS STRUCTURE
	const float floor_checkerboard_vertices[98] = // THIS IS JUST A QUICK TEST. I NEED TO INCLUDE A WHITE AND BLACK VERTEX FOR SOME COORDINATES WHICH IS A WASTE OF SPACE!
	{
		//Position:		       Color:
		 0.0f,   0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, //  0. Center:        black
		 0.0f,   0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  1. Center:        white
		 0.5f,   0.5f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  2. Top    right   white
		 0.0f,   0.5f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  3. Top    center  white
		 0.0f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, //  4. Top    center  black
		-0.5f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, //  5. Top    left    black
		-0.5f,   0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, //  6. Left   center  black
		-0.5f,   0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  7. Left   center  white
		-0.5f,  -0.5f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  8. Bottom left    white
		 0.0f,  -0.5f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //  9. Bottom center  white
		 0.0f,  -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, // 10. Bottom center  black
		 0.5f,  -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, // 11. Bottom right   black
		 0.5f,   0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, // 12. Right  center  black
		 0.5f,   0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, // 13. Right  center  white
	};
	const unsigned int floor_checkerboard_indices[24] = // Counter clockwise
	{
		// TOP RIGHT WHITE PLANE
		2,  3, 1,   // Top right white,     Top center white,     Center white
		1, 13, 2,   // Center white,        Right  center white,  Top right white
		// TOP LEFT BLACK PLANE
		4, 5, 6,    // Top center black,    Top left black,       Left center black
		6, 0, 4,    // Left center black,   Center black,         Top center black
		// BOTTOM LEFT WHITE PLANE
		1, 7, 8,    // Center white,        Left center white,    Bottom left white
		8, 9, 1,    // Bottom left white,   Bottom center white,  Center white
		// BOTTOM RIGHT BLACK PLANE
		12,  0, 10, // Right center black,  Center black,         Bottom center black
		10, 11, 12  // Bottom center black, Bottom right black,   Right center black
	};

public:
	Plane();
	~Plane() {}

	inline void Bind() const { vertex_array.Bind(); } // WATCH OUT: THIS METHOD DOES NOT CHECK IF THE VERTEX ARRAY IS DELETED !!! => TO DO: FIX THIS!

private:
	void InitBuffers();
	void InitVAO();
};

class Triangle_2D : public Primitive_Shape2D // Class not implemented yet
{
public:
	Triangle_2D() {}
	~Triangle_2D() {}
};

#endif // PRIMITIVE_SHAPES3D_H
#include "Geometry.h"

Geometry::Geometry(std::vector<float>* vertices, std::vector<unsigned int>* indices)
	: vertices(vertices), indices(indices)
{
	if (vertices != NULL && indices != NULL)
	{
		InitBuffers();
		InitVAO();
	}
	else
	{
		std::cout << "Vertices buffer or Indices buffer can't be NULL!" << std::endl;
	}
}

void Geometry::InitBuffers()
{
	buffer_vertices.Init(&(vertices->front()), vertices->size() * sizeof(float));
	buffer_indices.Init(&(indices->front()), indices->size());
}

void Geometry::InitVAO()
{
	buffer_vertices_layout.Push<float>(3);	// Push the amount of floats per vertex that are used for the vertex position
	vertex_array.AddBuffer(buffer_vertices, buffer_vertices_layout);
}

std::vector<float> Geometry_Cube::cube_vertices = // 24 vertices, BLENDER .ply EXPORT
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

std::vector<unsigned int> Geometry_Cube::cube_indices = // 36 indices, Counter clockwise
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
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GL_VertexArray.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"

class Geometry
{

friend class Mesh;

protected:
	GL_Vertex_Array       vertex_array;
	GL_VertexBuffer       buffer_vertices;
	GL_VertexBufferLayout buffer_vertices_layout;
	GL_ElementBuffer      buffer_indices;

	std::vector<float>* vertices = NULL;
	std::vector<unsigned int>* indices = NULL;

public:
	Geometry(std::vector<float>* vertices, std::vector<unsigned int>* indices);
	~Geometry() {}

private:
	void InitBuffers();
	void InitVAO();
};

class Geometry_Cube : public Geometry 
{
private:
	// Made the cube vertices and indices a static const because the data will be
	// the same for each cube that will be created while using this geometry.
	// This avoids duplicating the data for each instance of Geometry_Cube
	static std::vector<float>        cube_vertices;
	static std::vector<unsigned int> cube_indices;

public:
	Geometry_Cube() : Geometry(&cube_vertices, &cube_indices) {}
	~Geometry_Cube() {}
};

class Geometry_Triangle3D : public Geometry
{
private:
	static std::vector<float>        triangle_vertices;
	static std::vector<unsigned int> triangle_indices;

public:
	Geometry_Triangle3D() : Geometry(&triangle_vertices, &triangle_indices) {}
	~Geometry_Triangle3D() {}
};

//class Geometry_Pyramid : public Geometry
//{
//public:
//	Geometry_Pyramid() {}
//	~Geometry_Pyramid() {}
//};

#endif // GEOMETRY_H

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
	// This constructor unbinds all the GL buffers belonging to this geometry from the GL context after their creation and initialisation.
	Geometry(std::vector<float>* vertices, std::vector<unsigned int>* indices);
	~Geometry() {}


	inline void Unbind_GL_VAO()
	{
		GL_Vertex_Array::Unbind();
	}

	void Delete_GL_Buffers();

private:
	void InitBuffers();
	void InitVAO();

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	inline void Unbind_GL_Buffers()
	{
		GL_Vertex_Array::Unbind();
		GL_VertexBuffer::Unbind();   
		GL_ElementBuffer::Unbind();
	}
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

class Geometry_Pyramid : public Geometry
{
private:
	static std::vector<float>        pyramid_vertices;
	static std::vector<unsigned int> pyramid_indices;

public:
	Geometry_Pyramid() : Geometry(&pyramid_vertices, &pyramid_indices) {}
	~Geometry_Pyramid() {}
};

#endif // GEOMETRY_H

#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H

#include <vector>
#include "GL_ErrorHandeling.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"

class GL_Vertex_Array
{
private:
	unsigned int id;

public:
	GL_Vertex_Array();
	~GL_Vertex_Array();

	void AddBuffer(const GL_VertexBuffer& vb, const GL_VertexBufferLayout& layout);

	void Bind() const;
	static void Unbind();
	void Delete() const;
};

#endif // GL_VERTEX_ARRAY_H

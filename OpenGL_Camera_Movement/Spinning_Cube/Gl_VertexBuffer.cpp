#include "GL_Buffers.h"


GL_VertexBuffer::GL_VertexBuffer(const void* data, int size)
{
	// GL_Call(glGenBuffers(1, &handle));
	// GL_Call(glBindBuffer(GL_ARRAY_BUFFER, handle));
	// GL_Call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	Init(data, size);
}

GL_VertexBuffer::~GL_VertexBuffer()
{
	GL_Call(glDeleteBuffers(1, &handle));
}

void GL_VertexBuffer::Init(const void* data, int size) 
{
	if (is_initialised == false)
	{
		GL_Call(glGenBuffers(1, &handle));
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, handle));
		GL_Call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

		is_initialised = true;
	}
}

void GL_VertexBuffer::Bind() const /*const because this method doesn't modify data*/
{
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, handle));
}

void GL_VertexBuffer::Unbind()
{
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GL_VertexBuffer::Delete() const
{
	GL_Call(glDeleteBuffers(1, &handle));
}

void GL_VertexBuffer::Print() const
{
	std::cout << "Vertex buffer" << std::endl << "OpenGl Handle: " << handle << std::endl << std::endl;
}
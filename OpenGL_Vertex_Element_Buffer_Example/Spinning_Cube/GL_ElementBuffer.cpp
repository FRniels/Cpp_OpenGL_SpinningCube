#include "GL_Buffers.h"

GL_ElementBuffer::GL_ElementBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count) /* Count is used here instead of size. The count is saved to use it later on in the drawing calls of the renderer */
{
	/* Check if a GLuint is the same size as an unsigned int, else break -> 99.99% it will be the same */
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GL_Call(glGenBuffers(1, &handle));
	GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

GL_ElementBuffer::~GL_ElementBuffer()
{
	GL_Call(glDeleteBuffers(1, &handle));
}

void GL_ElementBuffer::Bind() const /* const because this method doesn't modify data */
{
	GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
}

void GL_ElementBuffer::Unbound() const
{
	GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void GL_ElementBuffer::Delete() const
{
	GL_Call(glDeleteBuffers(1, &handle));
}

void GL_ElementBuffer::Print() const
{
	std::cout << "Element buffer" << std::endl << "OpenGl Handle: " << handle << std::endl << "Indices: " << m_Count << std::endl << std::endl;
}
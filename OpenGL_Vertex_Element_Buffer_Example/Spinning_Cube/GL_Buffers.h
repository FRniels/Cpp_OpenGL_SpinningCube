#ifndef GL_BUFFERS_H
#define GL_BUFFERS_H

#include <iostream>
#include "GL/glew.h" 
#include "GL_ErrorHandeling.h"

class GL_Buffer
{
protected:
	unsigned int handle = 0;
public:
	GL_Buffer() {};

	~GL_Buffer() {};

	virtual void Bind() const = 0; 

	virtual void Unbound() const = 0;

	virtual void Delete() const = 0;

	virtual void Print() const = 0; // Just a test method
};

class GL_VertexBuffer : public GL_Buffer
{
public:
	GL_VertexBuffer(const void* data, int size);					 // This constructor binds and leaves the buffer bound to the OpenGL context
	~GL_VertexBuffer();

	void Bind() const;

	void Unbound() const;

	void Delete() const;

	void Print() const;
};

class GL_ElementBuffer : public GL_Buffer
{
private:
	unsigned int m_Count = 0;

public:
	GL_ElementBuffer(const unsigned int* data, unsigned int count);   // This constructor binds and leaves the buffer bound to the OpenGL context
	~GL_ElementBuffer();

	void Bind() const;

	void Unbound() const;

	void Delete() const;

	void Print() const;
};

#endif // GL_BUFFERS_H

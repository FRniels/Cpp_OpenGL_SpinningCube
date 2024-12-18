#ifndef GL_BUFFERS_H
#define GL_BUFFERS_H

#include <iostream>
#include "GL/glew.h" 
#include "GL_ErrorHandeling.h"

class GL_Buffer
{
protected:
	unsigned int handle = 0;
	bool is_initialised = false; // Used to check if the OpenGL buffer is already created. This avoids creating a new OpenGL buffer when the user instantiated a buffer with the parameterized constructor and calls Init() on that instance.

public:
	GL_Buffer() {};

	~GL_Buffer() {};

	virtual void Bind() const = 0; 

	virtual void Delete() const = 0;

	virtual void Print() const = 0;       
};

class GL_VertexBuffer : public GL_Buffer
{
public:
	GL_VertexBuffer() {}
	GL_VertexBuffer(const void* data, int size);					 // This constructor binds and leaves the buffer bound to the OpenGL context
	~GL_VertexBuffer();

	void Init(const void* data, int size);

	void Bind() const;

	static void Unbind();

	void Delete() const;

	void Print() const;
};

class GL_ElementBuffer : public GL_Buffer
{
private:
	unsigned int m_Count = 0;

public:
	GL_ElementBuffer() {}
	GL_ElementBuffer(const unsigned int* data, unsigned int count);   // This constructor binds and leaves the buffer bound to the OpenGL context
	~GL_ElementBuffer();

	void Init(const unsigned int* data, unsigned int count);

	void Bind() const;

	static void Unbind();

	void Delete() const;

	void Print() const;
};

#endif // GL_BUFFERS_H

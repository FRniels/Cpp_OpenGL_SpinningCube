#ifndef OBJECT_H
#define OBJECT_H

#include "GL_VertexArray.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"
#include "Transform.h"

class Object
{
private:
	static unsigned int id; // Initialised to 0 in the source file Object.cpp

protected:
	GL_Vertex_Array       vertex_array;
	GL_VertexBuffer       bufferV;
	GL_VertexBufferLayout layout_bufferV;
	GL_ElementBuffer      bufferE;

public:
	Transform transform;

public:
	Object() { ++id;  }
	~Object() {}

	// IMPORTANT: Always unbind the vao before unbinding the associated vertex/element buffer. If the vertex/element buffer is unbound before 
	//            the vao is unbound, the vertex/element will be unbound from the vao, thus the vao will not have the vertex/element buffer bound to it anymore.
	//            When trying to draw with such an 'unconfigured' vao, null pointer errors can/will or even worse, undefinded behaviour will occur.
	inline void Unbind_AllBuffers()
	{
		GL_Vertex_Array::Unbind();
		GL_VertexBuffer::Unbind();
		GL_ElementBuffer::Unbind();
	}

	inline void Unbind_VAO()
	{
		GL_Vertex_Array::Unbind();
	}

	void DeleteGLObjects()				              // THIS CLASS INSTANCE WILL NOT BE DELETED!
	{
		bufferV.Delete();
		bufferE.Delete();
		vertex_array.Delete();
	}
};

#endif // OBJECT_H

#ifndef VERTEX_BUFFER_LAYOUT_H 
#define VERTEX_BUFFER_LAYOUT_H 

#include <vector>
#include "GL/glew.h"  
#include "GL_ErrorHandeling.h"


struct GL_VertexBufferElement	  // Struct to hold each vertex element's argument values for glVertexAttribPointer()
{
	unsigned int count;
	unsigned int opengl_type; 
	unsigned char normalised;

	static unsigned int GetSizeOfType(unsigned int opengl_type)
	{
		switch (opengl_type)
		{
			case GL_UNSIGNED_BYTE:	return 1;
			case GL_UNSIGNED_INT:	return 4;
			case GL_FLOAT:			return 4;
		}
		ASSERT(false);
		return 0;
	}
};

class GL_VertexBufferLayout
{
private:
	std::vector<GL_VertexBufferElement> vertex_elements;
	unsigned int stride;

public:
	GL_VertexBufferLayout() : stride(0) {}
	~GL_VertexBufferLayout(){}

	template<typename T>
	void Push(unsigned int count) // count: quantity of coordinates per vertex
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) 
	{
		vertex_elements.push_back({ count, GL_FLOAT, GL_FALSE });
		stride += count * GL_VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		vertex_elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		stride += count * GL_VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		// Normalise an unsigned byte (char) => Normalizing an unsigned byte equals (unsigned byte value / 255) => Has to do with normalizing on the CPU vs GPU and minimizing memory consumption. => More research needed!
		vertex_elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });	 
		stride += count * GL_VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<GL_VertexBufferElement>& GetElements() const { return vertex_elements; }	// Pass by const& so that the type and data of the elements can't be changed. const& also avoid copying the vector when returning the vector.

	inline unsigned int GetStride() const { return stride; }
};

#endif // VERTEX_BUFFER_LAYOUT_H 
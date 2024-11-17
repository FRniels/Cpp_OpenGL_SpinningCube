#include "GL_VertexArray.h"

GL_Vertex_Array::GL_Vertex_Array()
{
	GL_Call(glGenVertexArrays(1, &id));
	GL_Call(glBindVertexArray(id));		 // The constructor binds the newly created vertex array object to the OpenGL context.
}

GL_Vertex_Array::~GL_Vertex_Array()
{
	GL_Call(glDeleteVertexArrays(1, &id));
}

void GL_Vertex_Array::AddBuffer(const GL_VertexBuffer& vb, const GL_VertexBufferLayout& layout)
{
	Bind();     // Bind the vertex array to the OpenGL context
	vb.Bind();  // Bind the user defined vertex buffer to the OpenGL context

	std::vector<GL_VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) // Loop through all the seperate vertex elements layout data stored in the vector => TO DO: REWATCH THE VIDEO OF THE CHERNO ON YOUTUBE TO FIGURE OUT WHY HE IS ENABLING EACH PREVIOUS VAO AGAIN WHEN ADDING A NEW LAYOUT ?? AND WHY THE OFFSET ??
	{
		const GL_VertexBufferElement& element = elements[i];
		GL_Call(glEnableVertexAttribArray(i));
		GL_Call(glVertexAttribPointer(i, element.count, element.opengl_type, element.normalised, layout.GetStride(), (const void*)offset));
		offset += element.count * GL_VertexBufferElement::GetSizeOfType(element.opengl_type); 
	}
}

void GL_Vertex_Array::Bind() const
{
	GL_Call(glBindVertexArray(id));
}

void GL_Vertex_Array::Unbind()
{
	GL_Call(glBindVertexArray(0));
}

void GL_Vertex_Array::Delete() const
{
	GL_Call(glDeleteVertexArrays(1, &id));
}
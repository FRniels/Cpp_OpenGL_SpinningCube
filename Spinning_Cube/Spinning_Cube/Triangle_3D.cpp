#include "Primitive_Shapes3D.h"

Triangle_3D::Triangle_3D()
{
	InitBuffers();
	InitVAO();
}

void Triangle_3D::InitBuffers()
{
	bufferV.Init(triangle_vertices, 6 * 3 * sizeof(float));
	bufferE.Init(triangle_indices, 8 * 3);
}

void Triangle_3D::InitVAO()
{
	layout_bufferV.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
	vertex_array.AddBuffer(bufferV, layout_bufferV);
}

void Triangle_3D::DeleteGLObjects()
{
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
}
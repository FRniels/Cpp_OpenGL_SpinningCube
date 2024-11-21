#include "Primitive_Shapes3D.h"

Cube::Cube()
{
	InitBuffers();
	InitVAO();
}

void Cube::InitBuffers()
{
	bufferV.Init(cube_vertices, 8 * 3 * sizeof(float));
	bufferE.Init(cube_indices, 12 * 3);
}

void Cube::InitVAO()
{
	layout_bufferV.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
	vertex_array.AddBuffer(bufferV, layout_bufferV);
}

void Cube::DeleteGLObjects()
{
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
}

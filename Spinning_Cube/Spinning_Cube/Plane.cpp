#include "Primitive_Shapes2D.h"

Plane::Plane() 
{ 
	InitBuffers();
	InitVAO(); 
}

void Plane::InitBuffers()
{
	bufferV.Init(floor_checkerboard_vertices, 14 * 7 * sizeof(float));
	bufferE.Init(floor_checkerboard_indices, 8 * 3);
}

void Plane::InitVAO()
{
	layout_bufferV.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
	layout_bufferV.Push<float>(4);								   // Push the amount of floats per vertex that are used for the vertex color
	vertex_array.AddBuffer(bufferV, layout_bufferV);
}

void Plane::DeleteGLObjects()
{
	bufferV.Delete();
	bufferE.Delete();
	vertex_array.Delete();
}

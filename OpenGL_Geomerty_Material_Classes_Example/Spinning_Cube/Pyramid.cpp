#include "Primitive_Shapes3D.h"

Pyramid::Pyramid()
{
	InitBuffers();
	InitVAO();
}

void Pyramid::InitBuffers()
{
	bufferV.Init(pyramid_vertices, 5 * 7 * sizeof(float));
	bufferE.Init(pyramid_indices, 6 * 3);
}

void Pyramid::InitVAO()
{
	layout_bufferV.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
	layout_bufferV.Push<float>(4);								   // Push the amount of floats per vertex that are used for the vertex color
	vertex_array.AddBuffer(bufferV, layout_bufferV);
}
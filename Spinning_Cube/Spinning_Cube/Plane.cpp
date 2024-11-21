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

// TO DO: THESE VERTICES SHOULD BE CONVERTED TO A UNITY PLANE AND THE CONVERTED VERTICES AND INDICES SHOULD BE USED IN THE PLANE CLASS WHEN THE PLANE CAN BE DYNAMICALLY CREATED
//float plane_vertices[] =
//{
//	//Position:		       Color:
//	 0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 0. Top right
//	-0.5f,   0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 1. Top left
//	-0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f, // 2. Bottom left
//	 0.5f,  -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, 1.0f  // 3. Bottom right
//};
//unsigned int plane_indices[] =	// Counter clockwise
//{
//	0, 1, 2,			        // Top right, top left, bottom left
//	2, 3, 0                     // Bottom left, bottom left, top right
//};

// THESE LINES USE floor_vertices[] and floor_indices[]
//GL_Vertex_Array vertex_array_floor;
//GL_VertexBuffer bufferV_floor(floor_vertices, 4 * 7 * sizeof(float));  // The vertex buffer is bound to the OpenGL context on instantiation
//GL_VertexBufferLayout layout_bufferV_floor;
//layout_bufferV_floor.Push<float>(3);								   // Push the amount of floats per vertex that are used for the vertex position
//layout_bufferV_floor.Push<float>(4);								   // Push the amount of floats per vertex that are used for the vertex color
//vertex_array_floor.AddBuffer(bufferV_floor, layout_bufferV_floor);
//GL_ElementBuffer bufferE_floor(floor_indices, 2 * 3);				   // The element buffer is bound to the OpenGL contect on instantiation

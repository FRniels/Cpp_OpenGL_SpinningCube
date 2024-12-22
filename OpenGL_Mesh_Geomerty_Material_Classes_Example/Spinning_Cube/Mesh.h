#ifndef MESH_H
#define MESH_H

#include "Object.h"
#include "Geometry.h"
#include "Material.h"

class Mesh : public Object
{
private:
	Geometry* geometry;
	Material* material;

public:
	Mesh(Geometry* geometry, Material* material) : geometry(geometry), material(material) 
	{ 
		ASSERT(geometry != NULL);  
		// ASSERT(material != NULL); // TO DO: UNCOMMENT WHEN ALL OBJECTS USE THE MATERIAL CLASS!
	}
	~Mesh() {}

	inline unsigned int GetIndicesCount() const { return geometry->GetIndicesCount(); }

	inline void Bind(ShaderManager& shader_manager) { geometry->vertex_array.Bind(); if(material) material->Bind(shader_manager); } // TO DO: REMOVE THE IF, THIS IS BECAUSE ONLY FLOOR HAS A MATERIAL FOR NOW!
	inline void Unbind(ShaderManager& shader_manager) { GL_Vertex_Array::Unbind(); shader_manager.UnbindShaderProgam(); }
	void Delete_GL_Buffers() { geometry->Delete_GL_Buffers(); }
};

#endif // MESH_H

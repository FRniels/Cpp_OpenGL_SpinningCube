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
		ASSERT(material != NULL); 
	}
	~Mesh() {}

	inline unsigned int GetIndicesCount() const { return geometry->GetIndicesCount(); }

	inline void Bind(ShaderManager& shader_manager) { geometry->vertex_array.Bind(); material->Bind(shader_manager); } 
	inline void Unbind(ShaderManager& shader_manager) { GL_Vertex_Array::Unbind(); shader_manager.UnbindShaderProgam(); }
	void Delete(ShaderManager& shader_manager) { geometry->Delete_GL_Buffers(); material->Delete(shader_manager); }
};

#endif // MESH_H

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
	Mesh(Geometry* geometry, Material* material) : geometry(geometry), material(material) {}
	~Mesh() {}

	inline unsigned int GetIndicesCount() const { return geometry->GetIndicesCount(); }

	inline void Bind()   { geometry->vertex_array.Bind(); }
	inline void Unbind() { GL_Vertex_Array::Unbind(); }
	void Delete_GL_Buffers() { geometry->Delete_GL_Buffers(); }
};

#endif // MESH_H

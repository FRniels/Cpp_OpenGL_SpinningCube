#ifndef OBJECT_H
#define OBJECT_H

#include "GL_VertexArray.h"
#include "GL_Buffers.h"
#include "GL_VertexBufferLayout.h"
#include "Transform.h"

class Object
{
private:
	static unsigned int id; // Initialised to 0 in the source file Object.cpp

public:
	Transform transform; // TO DO: THIS SHOULD NOT REALLY BE PUBLIC. FIND BETTER ALTERNATIVE

public:
	Object() { ++id;  }
	~Object() {}
};

#endif // OBJECT_H

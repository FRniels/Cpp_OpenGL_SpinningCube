#ifndef GL_UNIFORM_H
#define GL_UNIFORM_H

struct GL_Uniform
{
private:
	unsigned int handle;

public:
	GL_Uniform(unsigned int handle) : handle(handle) {}
	unsigned int Get_Handle() { return handle;  }
};

#endif; // GL_UNIFORM_H

#ifndef GL_USER_TYPES_H
#define GL_USER_TYPES_H

#define VEC2I_SIZE 2
typedef int   vec2i[VEC2I_SIZE]; // Typedefing an array of 2 ints   to be used like the GLSL (shader) type vec2

#define VEC2F_SIZE 2
typedef float vec2f[VEC2F_SIZE]; // Typedefing an array of 2 floats to be used like the GLSL (shader) type vec2

#define VEC3F_SIZE 3
typedef float vec3f[VEC3F_SIZE]; // Typedefing an array of 3 floats to be used like the GLSL (shader) type vec3

#define VEC4F_SIZE 4
typedef float vec4f[VEC4F_SIZE]; // Typedefing an array of 4 floats to be used like the GLSL (shader) type vec4

enum GL_ROTATION_AXIS
{
	GL_ROTATION_X_AXIS, GL_ROTATION_Y_AXIS, GL_ROTATION_Z_AXIS
};

#endif // GL_USER_TYPES_H

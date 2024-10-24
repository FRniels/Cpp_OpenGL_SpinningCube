#ifndef GL_DRAW_H
#define GL_DRAW_H

#include "GL/glew.h"
#include "GL_User_Types.h"
#include "GL_ErrorHandeling.h"

void GL_ClearColor(vec4f color);

void GL_ClearScreen(vec4f clear_color);

void DrawTriangle(vec2f coo1, vec2f coo2, vec2f coo3); // Note: This makes use of OpenGL legacy API calls => In actual applications, these GL calls should be replaced by GL calls that makes use of buffer/index objects

#endif // GL_DRAW_H

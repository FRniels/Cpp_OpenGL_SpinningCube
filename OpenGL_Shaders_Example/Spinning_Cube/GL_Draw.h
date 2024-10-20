#ifndef GL_DRAW_H
#define GL_DRAW_H

#include "GL/glew.h"
#include "GL_ErrorHandeling.h"

void GL_ClearScreen(void);

void DrawTriangle(void); // Note: This makes use of OpenGL legacy API calls => In actual applications, these GL calls should be replaced by GL calls that makes use of buffer/index objects

#endif // GL_DRAW_H

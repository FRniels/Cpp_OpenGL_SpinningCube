#include "GL_Draw.h"

void GL_ClearScreen(vec4f clear_color)
{
	// glClearColor(0.996F, 0.54F, 0.094F, 0.0F); // Orange
	glClearColor(*clear_color, *(clear_color + 1), *(clear_color + 2), *(clear_color + 3)); 
	GL_Call(glClear(GL_COLOR_BUFFER_BIT));
}

void DrawTriangle(void)
{
	GL_Call(glBegin(GL_TRIANGLES));
	GL_Call(glVertex2f(0.0f, 0.5f));
	GL_Call(glVertex2f(-0.5f, -0.5f));
	GL_Call(glVertex2f(0.5f, -0.5f));
	glEnd();
}
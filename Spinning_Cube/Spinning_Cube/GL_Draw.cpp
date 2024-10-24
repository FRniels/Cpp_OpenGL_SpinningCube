#include "GL_Draw.h"

void GL_ClearColor(vec4f color)
{
	glClearColor(*color, *(color + 1), *(color + 2), *(color + 3));
}

void GL_ClearScreen(vec4f clear_color)
{
	glClearColor(*clear_color, *(clear_color + 1), *(clear_color + 2), *(clear_color + 3));
	GL_Call(glClear(GL_COLOR_BUFFER_BIT));
}

void DrawTriangle(vec2f coo1, vec2f coo2, vec2f coo3)
{
	GL_Call(glBegin(GL_TRIANGLES));

	GL_Call(glVertex2f(*coo1, *(coo1 + 1)));
	GL_Call(glVertex2f(*coo2, *(coo2 + 1)));
	GL_Call(glVertex2f(*coo3, *(coo3 + 1)));

	glEnd();
}
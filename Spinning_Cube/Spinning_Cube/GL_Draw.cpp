#include "GL_Draw.h"

void GL_ClearScreen(vec4f clear_color)
{
	// glClearColor(0.996F, 0.54F, 0.094F, 0.0F); // Orange
	glClearColor(*clear_color, *(clear_color + 1), *(clear_color + 2), *(clear_color + 3)); 
	
	// Clear the screen
	GL_Call(glClear(GL_COLOR_BUFFER_BIT));
	// GL_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // TO DO: RESEARCH DEPTH TEST => IF DEPTH TEST IS ENABLED, THE CUBE DISAPPEARS
}

void DrawTriangle(vec2f coo1, vec2f coo2, vec2f coo3)
{
	GL_Call(glBegin(GL_TRIANGLES));

	/*GL_Call(glVertex2f(0.0f, 0.5f));
	GL_Call(glVertex2f(-0.5f, -0.5f));
	GL_Call(glVertex2f(0.5f, -0.5f));*/

	GL_Call(glVertex2f(*coo1, *(coo1 + 1)));
	GL_Call(glVertex2f(*coo2, *(coo2 + 1)));
	GL_Call(glVertex2f(*coo3, *(coo3 + 1)));

	glEnd();
}
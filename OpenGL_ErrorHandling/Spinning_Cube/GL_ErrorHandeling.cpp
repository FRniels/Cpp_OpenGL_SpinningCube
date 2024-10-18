#include "GL/glew.h"    
#include "GL_ErrorHandeling.h"

void GL_ClearAllErrors(void)
{
	/* This is a fail safe, if someone forgets to use our error handeling with an opengl call and does use it on a following opengl call.
	   In that case there could have been generated some errors from that opengl call without the error handeling wich aren't cleared.
	   This can result in wrong errors at that point.
	   An error can be cleared by actually retreiving the error value. Clear all the messages by going through them with a loop */
	while (glGetError() != GL_NO_ERROR);
}
#ifndef GL_ERROR_HANDELING
#define GL_ERROR_HANDELING

#include "GL/glew.h"  

struct HexaString;

#define ASSERT(x) if(!(x)) __debugbreak();

// assert true is just for quick testing
#ifdef _DEBUG
#define GL_Call(x) GL_ClearAllErrors();\
x;\
ASSERT(true)
#define GL_Call(x) x
#endif

void GL_ClearAllErrors(void);

void DecToHexa(GLenum errorCode, HexaString & storeHexValue);

#endif // GL_ERROR_HANDELING

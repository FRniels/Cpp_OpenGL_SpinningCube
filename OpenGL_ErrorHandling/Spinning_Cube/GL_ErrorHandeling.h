#ifndef GL_ERROR_HANDELING
#define GL_ERROR_HANDELING

#define ASSERT(x) if(!(x)) __debugbreak();

// assert true is just for quick testing
#ifdef _DEBUG
#define GL_Call(x) GL_ClearAllErrors();\
x;\
ASSERT(true)
#define GL_Call(x) x
#endif

void GL_ClearAllErrors(void);

#endif // GL_ERROR_HANDELING

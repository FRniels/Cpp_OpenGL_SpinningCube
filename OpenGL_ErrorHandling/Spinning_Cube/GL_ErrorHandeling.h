#ifndef GL_ERROR_HANDELING
#define GL_ERROR_HANDELING

#include "GL/glew.h"  

struct HexaString;

/*'x' is the function we pass in, if it returns false, we put a breakpoint on it
  Compiler intrinsic:'__debugbreak' is ONLY related to MSVC compiler, clang or gcc will use another one. */
#define ASSERT(x) if(!(x)) __debugbreak();

 /*Don't put a space after the \ before going to a new line: this wil insert a new line character! Thus you cannot write a comment next to those lines!
   This macro will first clear all previous errors, execute our code (x) and puts a breakpoint in the debugger if an error occured */
#ifdef _DEBUG
	#define GL_Call(x) GL_ClearAllErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // #x converts the function name to text -> don't put a semicolon here because this is done when calling GLCall()
#else
	#define GL_Call(x) x
#endif

void GL_ClearAllErrors(void);

void DecToHexa(GLenum errorCode, HexaString & storeHexValue);

void PrintGlewErrorCode(const std::string & filePath, HexaString & hexErrorCode);

bool GLLogCall(const char* function, const char* file, int line);

#endif // GL_ERROR_HANDELING

# GLEW Library

This library provides the headers for OpenGL functionality and retrieves pointers to the OpenGL functions based on the graphics drivers you are using.

## Explanation of the Library

The functionality of OpenGL is located in the drivers of your graphics card. We need to "pull out" that functionality by retrieving 
the function declarations and linking against them. To achieve this, we need to access the driver DLL files and retrieve function pointers 
to the functions in those DLL files.

While we could do this ourselves, it would be a **lot of work**! One reason is that there are many functions, 
plus cross-platform compatibility needs to be considered. For example, on a Windows machine, we can use the WIN32 API to get these function pointers, 
but on Mac, it's another API.

You can download the 32-bit binaries from (or for more serious projects, build the binaries yourself):
[http://glew.sourceforge.net/](http://glew.sourceforge.net/)

## Setup Steps

1. Put the entire GLEW folder content into the folder: `$(SolutionDir)Dependencies\GLEW\`.
2. Add the GLEW include folder:
   - Project -> Properties -> C++ -> General -> `Additional Include Directories`.
3. Add the GLEW lib folder:
   - Project -> Properties -> Linker -> General -> `Additional Library Directories`: `$(SolutionDir)Dependencies\GLEW\lib\Release\Win32`.
4. Link to the library:
   - Project -> Properties -> Linker -> Input -> Add `glew32s.lib` to the `Additional Dependencies`.
5. Define `GLEW_STATIC` (we use static linking, so no DLL):
   - Project -> Properties -> C++ -> Preprocessor -> Add `GLEW_STATIC;` to `Preprocessor Definitions`.

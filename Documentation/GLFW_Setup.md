# GLFW Setup

## Setting up GLFW: Static Linking

1. Download GLFW binaries from their website (I use 32-bit, so I target a 32-bit platform).
2. Create a new folder structure: `Dependencies -> GLFW` in the solution folder.
3. From the GLFW download, copy the `lib-vc2019` and `include` folder and paste them into `Dependencies -> GLFW`.
   - Using `lib-vc2019 -> glfw3.lib` because of static linking (so no dll).

4. Open up project configurations:
   - Right-click on the project -> Properties.
5. Ensure "All Configurations" and "Win32" are selected (I'm on a Windows machine).
6. Add the GLFW include folder:
   - C++ -> General -> `AdditionalIncludeDirectories`: `$(SolutionDir)Dependencies\GLFW\include`
   - `$(SolutionDir)` is the path to the solution file and already contains a backslash (`\`).

7. Link the library:
   - Right-click the project -> Properties -> Ensure "All Configurations" and "Win32" are selected.
   - Linker -> General -> `Additional Library Directories`: `$(SolutionDir)Dependencies\GLFW\lib-vc2019`.

8. Linker -> Input -> `Additional Dependencies`, add: `glfw3.lib`.
9. Link to OpenGL:
   - Linker -> Input -> `Additional Dependencies`, add: `opengl32.lib`.

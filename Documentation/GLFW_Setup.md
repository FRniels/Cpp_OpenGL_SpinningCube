# GLFW Setup

Setting up GLFW: -> static linking
1.) Download GLFW binaries from their website (I use 32bit -> so i TARGET a 32bit platform)7
2.) Create a new folder structure 'Dependencies -> GLFW' in the solution folder
3.) From the GLFW download, copy the lib-vc2019 and include folder and paste it in 'Dependencies -> GLFW'
	(Using lib-vc2019 -> glfw3.lib because of static linking (so no dll))

4.) Open up project configurations -> right click project -> properties
5.) Make sure 'all configurations' and 'win32' is set (I'm on a windows machine)
6.) Add a the GLFW include folder: C++ -> General -> AdditionalIncludeDirectories: $(SolutionDir)BasicOpenGl\Dependencies\GLFW\include
	  $(SolutionDir) is the path to the solution file, this already contains a backslash '\' 
7.) Link the library:
	  Right click project -> properties -> all configuration + win32 set
	  Linker -> General -> Additional Library Directories: $(SolutionDir)Dependencies\GLFW\lib-vc2019
8.) Linker -> Input -> Additional Dependecies add: glfw3.lib;
9.) Link to OpenGl:
	Linker -> Input -> Additional Dependecies add: opengl32.lib;
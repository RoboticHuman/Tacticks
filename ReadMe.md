To add file to the compilation list just put the name of the file in my.proj.
Only put the cpp files without the .o extension.
eg.
	to compile Main.cpp, classA.cpp and classB.cpp
	it should be as follows:
	Main
	classA
	classB

Simple enough ya Don? :D

By default the make file will check 'my.proj' for files names. However if you want a specific files to be compiled (maybe a sub-project?) use 'make FileSrc=SomeOtherFile.proj'. We should not really need to do this for since there are better solutions (branches maybe?) but it is just a quick way until we decide how to move on.

To check that the environment is setup properly run: make envCheck

P.S. this is a dummy ReadMe until we settle on one :D

Dependencies:
	SDL			2.0.4
	GLEW		2.0.0
	OpenGL		3.3 (Core Profile)
	GLM			0.9.7
	Assimp		3.2.71805284
P.S. Those are the versions that I (Dan) am working with. That doesn't mean it will not work with other versions. It would be nice to to find to decide on a version and everyone upgrade to that version.

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

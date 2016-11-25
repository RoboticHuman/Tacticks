.PHONY: first build clean run
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
AppName = CatnMouse.so
CleanFiles = *.log
IPath = .
LPath = .
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs =
Objects = Behaviour.o

first: build

build: $(AppName)

clean:
	rm -rf $(AppName) $(CleanFiles) *.out *.so *.dll

$(AppName): $(Objects)
	$(CXX) $(Objects) -o $(AppName) $(Libs) $(LinkFlags) -L$(LPath)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(IPath)

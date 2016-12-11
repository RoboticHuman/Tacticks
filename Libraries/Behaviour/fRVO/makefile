.PHONY: first build clean run
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
AppName = RVO.so
CleanFiles = *.log
IPath = .
LPath = .
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs = -lTacticks
Objects = $(addsuffix .o, $(basename $(wildcard *.cpp)))

ifeq ($(shell uname), Darwin)
	CompileFlags += -m32
	LinkFlags += -m32
endif

first: build

build: $(AppName)

clean:
	rm -rf $(AppName) $(CleanFiles) *.out *.so *.dll *.o

$(AppName): $(Objects)
	$(CXX) $(Objects) -o $(AppName) $(Libs) $(LinkFlags) -L$(LPath)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(IPath)

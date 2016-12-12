.PHONY: first build clean run
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
AppName = Test.out
CleanFiles = *.log
IPath = .
LPath = .
CompileFlags = -std=c++11
LinkFlags =
Libs = -lTacticks
Objects = main.o

ifeq ($(shell uname), Darwin)
	CompileFlags += -m32
	LinkFlags += -m32
endif

first: build

build: $(AppName)

clean:
	rm -rf $(AppName) $(CleanFiles) *.out *.so *.dll *.o

run: $(AppName)
	@./$(AppName)

$(AppName): $(Objects)
	$(CXX) $(Objects) -o $(AppName) $(Libs) $(LinkFlags) -L$(LPath)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(IPath)

.PHONY: first build clean
AppName = NLrcHeightfield.so
CleanFiles = *.log
IPath = .
LPath = .
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs = 

Objects = $(addsuffix .o, $(basename $(wildcard *.cpp)))

first: build

build: $(AppName)

clean:
	rm -rf $(AppName) $(CleanFiles) *.out *.so *.dll *.o

$(AppName): $(Objects)
	$(CXX) $(Objects) -o $(AppName) $(LinkFlags) $(Libs) -L$(LPath)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(HDir) -I$(IPath)
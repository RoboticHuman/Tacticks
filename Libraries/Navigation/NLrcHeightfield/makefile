.PHONY: first build clean
AppName = NLrcHeightfield.so
CleanFiles = *.log
IPath = .
LPath = .
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs =
tempIPath = ./Recast/Include

Objects = $(addsuffix .o, $(basename $(wildcard *.cpp) $(wildcard Recast/Source/*.cpp)))

first: build

build: $(AppName)

clean:
	rm -rf $(AppName) $(CleanFiles) *.out *.so *.dll *.o

$(AppName): $(Objects)
	$(CXX) $(Objects) -o $(AppName) $(LinkFlags) $(Libs) -L$(LPath)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(IPath) -I$(tempIPath)

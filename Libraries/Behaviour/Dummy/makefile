.PHONY: first build clean run
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
FileSrc = Dummy.proj
AppName = Dummy.so
CleanFiles = *.log
SDir = ./src
HDir = ./include
BDir = ./Build
IPath = .
LPath = .
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs =

Objects = $(addsuffix .o, $(addprefix $(BDir)/, $(shell cat $(FileSrc))))
FolderList = $(sort $(SDir)/ $(HDir)/ $(BDir)/ $(dir $(Objects)) $(dir $(AppName)))

first: build

build: $(AppName)

clean:
	rm -rf $(BDir)/* $(AppName) $(CleanFiles) *.out *.so *.dll

run: $(AppName)
	./$(AppName)

$(AppName): $(Objects) | $(FolderList)
	$(CXX) $(Objects) -o $(AppName) $(Libs) $(LinkFlags) -L$(LPath)

$(BDir)/%.o: $(SDir)/%.cpp | $(FolderList)
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(HDir) -I$(IPath)

$(FolderList):
	mkdir -p $@

.PHONY: first build clean run install
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
InstallFolder = /usr
FileSrc = Engine.proj
AppName = libTacticks.so
CleanFiles = *.log
SDir = ./src
HDir = ./include
BDir = ./Build
CompileFlags = -std=c++11 -fPIC
LinkFlags = -shared
Libs = -ldl

Objects = $(addsuffix .o, $(addprefix $(BDir)/, $(shell cat $(FileSrc))))
FolderList = $(sort $(SDir)/ $(HDir)/ $(BDir)/ $(InstallFolder)/lib $(InstallFolder)/include/Tacticks $(dir $(Objects)) $(dir $(AppName)))

first: build

build: $(AppName)

clean:
	rm -rf $(BDir)/* $(AppName) $(CleanFiles) *.out *.so *.dll *.o

run: $(AppName)
	./$(AppName)

$(AppName): $(Objects) | $(FolderList)
	$(CXX) $(Objects) -o $(AppName) $(LinkFlags) $(Libs)

$(BDir)/%.o: $(SDir)/%.cpp | $(FolderList)
	$(CXX) -c $< -o $@ -I$(HDir) $(CompileFlags)

$(FolderList):
	mkdir -p $@

install: $(AppName) | $(FolderList)
	cp $(AppName) $(InstallFolder)/lib
	cp -r $(HDir)/* $(InstallFolder)/include/Tacticks

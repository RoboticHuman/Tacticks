.PHONY: first build clean run
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
FileSrc = Editor.proj
AppName = TacticksEditor.out
CleanFiles = *.log
SDir = ./src
HDir = ./include
BDir = ./Build
IPath = .
LPath = .
CompileFlags = -std=c++11
LinkFlags = `sdl2-config --libs`
Libs = -lSOIL -lGLEW -lTacticks -lassimp

ifeq ($(shell uname), Darwin)
	CompileFlags += -m32
	LinkFlags += -m32
	Libs += -framework OpenGL -framework Awesomium
else
	Libs += -lGL -lawesomium-1-7
endif

Objects = $(addsuffix .o, $(addprefix $(BDir)/, $(shell cat $(FileSrc))))
FolderList = $(sort $(SDir)/ $(HDir)/ $(BDir)/ $(dir $(Objects)) $(dir $(AppName)))

first: build

build: $(AppName)

clean:
	rm -rf $(BDir)/* $(AppName) $(CleanFiles) *.out *.so *.dll

run: $(AppName)
	@./$(AppName)

$(AppName): $(Objects) | $(FolderList)
	$(CXX) $(Objects) -o $(AppName) $(Libs) $(LinkFlags) -L$(LPath)

$(BDir)/%.o: $(SDir)/%.cpp | $(FolderList)
	$(CXX) -c $< -o $@ $(CompileFlags) -I$(HDir) -I$(IPath)

$(FolderList):
	mkdir -p $@

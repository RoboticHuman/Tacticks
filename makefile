.PHONY: first build clean run envCheck
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
FileSrc = my.proj
AppName = Tacticks.out
CleanFiles = *.log
SDir = ./src
HDir = ./include
BDir = ./Build
CompileFlags = -std=c++11
LinkFlags = `sdl2-config --libs`
Libs = -lsoil -lGL -lGLEW -lassimp
Objects = $(addsuffix .o, $(addprefix $(BDir)/, $(shell cat $(FileSrc))))
FolderList = $(sort $(SDir)/ $(HDir)/ $(BDir)/ $(dir $(Objects)) $(dir $(AppName)))

first: build

build: $(AppName)

clean:
	rm -rf $(BDir)/* $(AppName) $(CleanFiles) *.out

run: $(AppName)
	./$(AppName)

$(AppName): $(Objects) | $(FolderList)
	$(CXX) $(Objects) -o $(AppName) $(LinkFlags) $(Libs)

$(BDir)/%.o: $(SDir)/%.cpp | $(FolderList)
	$(CXX) -c $< -o $@ -I$(HDir) $(CompileFlags)

$(FolderList):
	mkdir -p $@

envCheck:
	@make AppName=envCheck.out FileSrc=envCheck.proj build run -s

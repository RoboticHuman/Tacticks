.PHONY: first clean engine editor libraries
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
EditorAppName = TacticksEditor.out
EngineLibName = Tacticks.so
InstallFolder = Install
CleanFiles = *.log $(InstallFolder)
MakeFlags = --no-print-directory
RunApp = $(EditorAppName)
SampleDir = ./Samples
SampleList = $(sort $(dir $(wildcard $(SampleDir)/*/)))
first: all

all: engine editor libraries

editor: engine
	@(cd Editor/ && make $(MakeFlags) IPath=../$(InstallFolder)/include LPath=../$(InstallFolder)/lib)

engine:
	@(cd Engine/ && make $(MakeFlags) install InstallFolder=../$(InstallFolder))

libraries: engine
	@(cd Libraries/ && make $(MakeFlags) IPath=../$(InstallFolder)/include LPath=../$(InstallFolder)/lib)

clean:
	@(cd Engine/ && make $(MakeFlags) clean)
	@(cd Editor/ && make $(MakeFlags) clean)
	@(cd Libraries/ && make $(MakeFlags) clean)
	@$(foreach sample, $(SampleList), (cd $(sample) && make $(MakeFlags) clean);)
	rm -rf $(CleanFiles) *.out *.so *.dll
#cleaning samples is missing

run: all
ifeq ($(RunApp), $(EditorAppName))
	@(export LD_LIBRARY_PATH=$(RootDir)Install/lib/:$$LD_LIBRARY_PATH && ./Editor/TacticksEditor.out)
else
	@(cd Samples/$(RunApp)/ && make $(MakeFlags) IPath=../../$(InstallFolder)/include LPath=../../$(InstallFolder)/lib)
	@(export LD_LIBRARY_PATH=$(RootDir)Install/lib/:$$LD_LIBRARY_PATH && ./Samples/$(RunApp)/$(RunApp).out)
endif

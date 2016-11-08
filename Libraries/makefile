.PHONY: first clean
RootDir = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
CleanFiles = *.log $(InstallFolder)
IPath = .
BehDir = ./Behaviour
NavDir = ./Navigation
BehList = $(sort $(dir $(wildcard $(BehDir)/*/)))
NavList = $(sort $(dir $(wildcard $(NavDir)/*/)))

first: all

all:
	$(foreach beh, $(BehList), @(cd $(beh) && make LPath=../../$(LPath) IPath=../../$(IPath)))
	$(foreach nav, $(NavList), @(cd $(nav) && make LPath=../../$(LPath) IPath=../../$(IPath)))

clean:
	$(foreach beh, $(BehList), @(cd $(beh) && make clean))
	$(foreach nav, $(NavList), @(cd $(nav) && make clean))

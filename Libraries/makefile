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
	$(foreach beh, $(BehList), @(cd $(beh) && make IPath=../../$(IPath) LPath=../../$(LPath)))
	$(foreach nav, $(NavList), @(cd $(nav) && make IPath=../../$(IPath) LPath=../../$(LPath)))

clean:
	$(foreach beh, $(BehList), @(cd $(beh) && make clean))
	$(foreach nav, $(NavList), @(cd $(nav) && make clean))

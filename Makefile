# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:42 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for my module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := GeDet
G4TARGET := $(name)
G4EXLIB := true
G4OPTDEBUG := true

#ifndef G4INSTALL
#  G4INSTALL = ../../
#endif

EXTRALIBS += ${shell $(ROOTSYS)/bin/root-config --libs}
CPPFLAGS += -I${ROOTSYS}/include

#G4ANALYSIS_USE := true

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk


CATAPULT_HOME := /home/stergios/Documents/libraries
SYSTEMC_HOME :=  /home/stergios/Documents/libraries/systemc-2.3.3

CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-label
#-Wall -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-label

USER_FLAGS = -DCONNECTIONS_ACCURATE_SIM -DSC_INCLUDE_DYNAMIC_PROCESSES

# RAND_STALL
# 0 = Random stall of ports and channels disabled (default)
# 1 = Random stall of ports and channels enabled
#
# This feature aids in latency insensitive design verication.
# Note: Only valid if SIM_MODE = 1 (accurate) or 2 (fast)
ifeq ($(RAND_STALL),1)
	USER_FLAGS += -DCONN_RAND_STALL
endif

INCDIRS = -isystem $(SYSTEMC_HOME)/include
INCDIRS += -isystem $(CATAPULT_HOME)/ac_simutils/include/
INCDIRS += -isystem $(CATAPULT_HOME)/matchlib_connections/include/
INCDIRS += -isystem $(CATAPULT_HOME)/ac_types/include/
INCDIRS += -isystem $(SYSTEMC_HOME)/src/

LIBDIR = -L. -L$(SYSTEMC_HOME)/lib-linux64 -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64
LIBS = -lsystemc

CPPFLAGS = $(CXXFLAGS)
CPPFLAGS += $(USER_FLAGS)
CPPFLAGS += $(INCDIRS)

.PHONY: all build run clean sim_clean help
.DEFAULT_GOAL := all
all: run

build: sim_sc

run: build
	./sim_sc

sim_sc: tb.cc switchBL.h Makefile 
	$(CXX) -o sim_sc ./tb.cc $(CPPFLAGS) $(LIBDIR) $(LIBS)

clean:
	rm -f sim_sc
	


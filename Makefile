#This makefile is the template for SystemC makefiles
SYSTEMC_ARCH = linux64

SYSTEMC=/usr/local/systemc-2.3.1
CATAPULT_HOME := /home/stergios/Documents/libraries

LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

#INCLUDE DIRECTORIES
INCLUDE_DIRS= -I. -I$(SYSTEMC)/include
INCLUDE_DIRS += -isystem $(CATAPULT_HOME)/ac_simutils/include/
INCLUDE_DIRS += -isystem $(CATAPULT_HOME)/matchlib_connections/include/
INCLUDE_DIRS += -isystem $(CATAPULT_HOME)/ac_types/include/
INCLUDE_DIRS += -isystem $(SYSTEMC)/src/

HEADERS =  switch.h tb.h

SOURCES = main.cc tb.cc 

DEPENDENCIES = \
		Makefile \
		$(HEADERS) \
		$(SOURCES) 
		
LIBS = -lsystemc -lstdc++ -lm 

TESTS=main

all: $(TESTS)
		./$(TESTS)
#		@make cmp_result
		
$(TESTS): $(DEPENDENCIES) 		
	gcc -std=c++98 -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS) 
	
clean:
	rm -f $(TESTS) *.dat
	
#to work this Makefile i create a file with name "systemc.conf"
#to this folder /etc/ld.so.conf.d
#The file contains this string "/usr/local/systemc-2.3.1/lib-linux64"
#and the i use this command "sudo ldconfig"

#ref_output.dat file created using xl

#GOLD_DIR = ./golden
#GOLD_FILE = $(GOLD_DIR)/ref_output.dat
#
#cmp_result:
#		@echo "********************************************************"
#		@if diff -w $(GOLD_FILE) ./output.dat; then \
#			echo "SIMULATION PASSED"; \
#		else \
#			echo "SIMULATION FAILED"; \
#		fi
#		@echo "********************************************************"
#

CXX=g++

PROGS=papi

CXXFLAGS=-g -Wall -std=c++17

all:$(PROGS)

tags: *.cc *.h 
	ctags *

papi: papi.o lisdata.o numtempl.o grammar.o compiling.o 
	$(CXX) -o $@ $^

depend:
	makedepend -Y 2> /dev/null *.cc *.c

clean:
	rm -f tags *.o Makefile.bak core* .gdb_history $(PROGS)

# DO NOT DELETE THIS LINE.

compiling.o: compiling.h info.h lisdata.h numtempl.h parser.h
grammar.o: grammar.h compiling.h info.h lisdata.h numtempl.h parser.h trow.h
lisdata.o: lisdata.h
numtempl.o: compiling.h info.h lisdata.h numtempl.h parser.h
papi.o: grammar.h compiling.h info.h lisdata.h numtempl.h parser.h trow.h
papi.o: metagenerated.h

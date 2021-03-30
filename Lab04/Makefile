CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11

test: roster.o
	$(CPP) $(OPTS) -o test roster.o 
	./test

roster: roster.o 
	$(CPP) $(OPTS) -o roster roster.o
	./roster cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

roster.o: roster.cpp
	$(CPP) $(OPTS) -c roster.cpp 

rosterObject: rosterObject.o 
	$(CPP) $(OPTS) -o rosterObject rosterObject.o
	./rosterObject cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

rosterObject.o: rosterObject.cpp
	$(CPP) $(OPTS) -c rosterObject.cpp 


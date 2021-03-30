CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11

testHashmap: testHashmap.o 
	$(CPP) $(OPTS) -o testHashmap testHashmap.o
	./testHashmap

testHashmap.o: testHashmap.cpp hashmap.hpp Makefile
	$(CPP) $(OPTS) -c testHashmap.cpp -o testHashmap.o

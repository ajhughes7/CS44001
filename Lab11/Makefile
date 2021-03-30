CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11


drink: drink.o 
	$(CPP) $(OPTS) -o drink drink.o 
	./drink

drink.o: drink.cpp Makefile drink.hpp
	$(CPP) $(OPTS) -c drink.cpp -o drink.o

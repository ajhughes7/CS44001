CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11

test: apples.o oranges.o
	$(CPP) $(OPTS) -o test apples.o oranges.o
	./test

apples: apples.o 
	$(CPP) $(OPTS) -o apples apples.o

apples.o: apples.cpp
	$(CPP) $(OPTS) -c apples.cpp 

oranges: oranges.o 
	$(CPP) $(OPTS) -o oranges oranges.o
	./oranges 

oranges.o: oranges.cpp
	$(CPP) $(OPTS) -c oranges.cpp 

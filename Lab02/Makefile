CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11

all: test wordcount

test: WordList.o testWordList.o WordOccurrence.o
	$(CPP) $(OPTS) -o test WordOccurrence.o WordList.o testWordList.o 
	./test

wordcount: WordList.o WordOccurrence.o main.o 
	$(CPP) $(OPTS) -o wordcount WordOccurrence.o WordList.o main.o
	./wordcount sample.txt

WordList.o: WordList.cpp WordOccurrence.o
	$(CPP) $(OPTS) -c WordList.cpp 

WordOccurrence.o: WordOccurrence.cpp
	$(CPP) $(OPTS) -c WordOccurrence.cpp

testWordList.o: WordList.hpp WordList.cpp testWordList.cpp
	$(CPP) $(OPTS) -c WordList.cpp testWordList.cpp

main.o: WordList.hpp WordList.cpp main.cpp
	$(CPP) $(OPTS) -c WordList.cpp main.cpp

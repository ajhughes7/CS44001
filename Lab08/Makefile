CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11



logger: logger.o 
	$(CPP) $(OPTS) -o logger logger.o
	./logger

logger.o: logger.cpp Makefile
	$(CPP) $(OPTS) -c logger.cpp -o logger.o


templateMethodGames: templateMethodGames.o 
	$(CPP) $(OPTS) -o templateMethodGames templateMethodGames.o
	./templateMethodGames

templateMethodGames.o: templateMethodGames.cpp Makefile
	$(CPP) $(OPTS) -c templateMethodGames.cpp -o templateMethodGames.o

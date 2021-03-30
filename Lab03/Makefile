CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11

test: uselist.o
	$(CPP) $(OPTS) -o test uselist.o 
	./test

testCollection: testCollection.o Collection.hpp
	$(CPP) $(OPTS) -o testCollection testCollection.o
	./testCollection 

uselist.o: list.hpp uselist.cpp
	$(CPP) $(OPTS) -c uselist.cpp

#Collection.o: Collection.cpp Collection.hpp
#	$(CPP) $(OPTS) -c Collection.cpp

testCollection.o: Collection.hpp testCollection.cpp 
	$(CPP) $(OPTS) -c testCollection.cpp 

clean:
	rm *.o
	rm test
	rm testCollection

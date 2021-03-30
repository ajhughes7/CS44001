CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11



bridgeFigures: bridgeFigures.o 
	$(CPP) $(OPTS) -o bridgeFigures bridgeFigures.o
	./bridgeFigures

bridgeFigures.o: bridgeFigures.cpp Makefile
	$(CPP) $(OPTS) -c bridgeFigures.cpp -o bridgeFigures.o


CarBuyer: CarBuyer.o CarFactory.o
	$(CPP) $(OPTS) -o CarBuyer CarBuyer.o CarFactory.o
	./CarBuyer

CarBuyer.o: CarBuyer.cpp CarFactory.hpp Makefile
	$(CPP) $(OPTS) -c CarBuyer.cpp -o CarBuyer.o 


CarTest: CarTest.o CarFactory.o
	$(CPP) $(OPTS) -o CarTest CarTest.o CarFactory.o
	./CarTest

CarTest.o: CarTest.cpp CarFactory.hpp Makefile
	$(CPP) $(OPTS) -c CarTest.cpp -o CarTest.o 


CarFactory.o: CarFactory.cpp CarFactory.hpp Makefile
	$(CPP) $(OPTS) -c CarFactory.cpp -o CarFactory.o 

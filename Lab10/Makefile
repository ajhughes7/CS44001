CPP  = clang++
OPTS = -g -Wall -W -Wunused -Wuninitialized -Wshadow -std=c++11



AdapterClass: AdapterClass.o 
	$(CPP) $(OPTS) -o AdapterClass AdapterClass.o
	./AdapterClass

AdapterClass.o: AdapterClass.cpp Makefile
	$(CPP) $(OPTS) -c AdapterClass.cpp -o AdapterClass.o

AdapterObject: AdapterObject.o 
	$(CPP) $(OPTS) -o AdapterObject AdapterObject.o
	./AdapterObject

AdapterObject.o: AdapterObject.cpp Makefile
	$(CPP) $(OPTS) -c AdapterObject.cpp -o AdapterObject.o


figuresPrivateInheritance: figuresPrivateInheritance.o figuresPrivateInheritance.o
	$(CPP) $(OPTS) -o figuresPrivateInheritance figuresPrivateInheritance.o
	./figuresPrivateInheritance

figuresPrivateInheritance.o: figuresPrivateInheritance.cpp Makefile
	$(CPP) $(OPTS) -c figuresPrivateInheritance.cpp -o figuresPrivateInheritance.o 

Process: Process.o 
	$(CPP) $(OPTS) -o Process Process.o
	./Process

Process.o: Process.cpp Makefile
	$(CPP) $(OPTS) -c Process.cpp -o Process.o

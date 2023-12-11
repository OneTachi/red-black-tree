BINARIES=RBtree

all:	${BINARIES}

RBtree: main.cpp
	g++ -std=c++11 -g main.cpp -o RBtree

Timer.o: Timer.cpp
	g++ -std=c++11 -g Timer.cpp -o Timer.o

clean:
	/bin/rm -rf *.o *~ ${BINARIES}

BINARIES=RBtree

all:	${BINARIES}

RBtree: main.cpp 
	g++ -std=c++11 -g main.cpp -o RBtree

clean:
	/bin/rm -rf *.o *~ ${BINARIES}

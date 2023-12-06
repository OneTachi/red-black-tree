BINARIES=hashcheck

all:	${BINARIES}

hashcheck: main.cpp 
	g++ -std=c++11 main.cpp -o RBtree

clean:
	/bin/rm -rf *.o *~ ${BINARIES}

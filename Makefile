CFLAGS= -Wall
CC=gcc

all: test1 oracle

test1: test1.o pile.o
	$(CC) $(CFLAGS) test1.o pile.o -o test1

oracle: oracle.o
	$(CC) $(CFLAGS) oracle.o -o oracle
clean:
	rm -f test1 oracle *.o

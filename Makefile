CC=gcc
CFLAGS=-Wall
RM=rm -rf
OUT=test

all: build

build: heap.o vector.o matrix.o node.o test.o
	$(CC) $(CFLAGS) -o $(OUT) heap.c vector.c matrix.c node.c test.c
	$(RM) *.o

clean:
	$(RM) *.o $(OUT)

debug: CFLAGS+=-DDEBUG_ON
debug: build

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

test.o: test.c vector.h
	$(CC) $(CFLAGS) -g -O0 -c test.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

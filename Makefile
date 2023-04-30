CC=gcc
CFLAGS=-Wall
RM=rm -rf
OUT=test

all: build

build: test.o vector.o malloc.o
	$(CC) $(CFLAGS) -o $(OUT) test.c vector.c malloc.c
	$(RM) *.o

debug: CFLAGS+=-DDEBUG_ON
debug: build

test.o: test.c vector.h
	$(CC) $(CFLAGS) -c test.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

malloc.o: malloc.c malloc.h
	$(CC) $(CFLAGS) -c malloc.c

clean:
	$(RM) *.o $(OUT)
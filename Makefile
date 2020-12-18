CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: hash.o

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c -o hash.o

clean:
	rm hash.o
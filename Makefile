CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: hash.o htest1 htest2 htest3 htest4

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c -o hash.o

htest1.o: htest1.c
	$(CC) $(CFLAGS) -c htest1.c -o htest1.o

htest2.o: htest2.c
	$(CC) $(CFLAGS) -c htest2.c -o htest2.o

htest3.o: htest3.c
	$(CC) $(CFLAGS) -c htest3.c -o htest3.o

htest4.o: htest4.c
	$(CC) $(CFLAGS) -c htest4.c -o htest4.o

htest1: hash.o htest1.o
	$(CC) $(CFLAGS) hash.o htest1.o -o htest1

htest2: hash.o htest2.o
	$(CC) $(CFLAGS) hash.o htest2.o -o htest2

htest3: hash.o htest3.o
	$(CC) $(CFLAGS) hash.o htest3.o -o htest3

htest4: hash.o htest4.o
	$(CC) $(CFLAGS) hash.o htest4.o -o htest4

clean:
	rm hash.o htest1.o htest2.o htest3.o htest4.o htest1 htest2 htest3 htest4
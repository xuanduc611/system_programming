CC = gcc

all: my_cat

my_cat: my_cat.o
	$(CC) my_cat.o -o my_cat

my_cat.o: my_cat.c
	$(CC) -Wall -c my_cat.c

clean:
	rm -rf *.o
	rm -rf my_cat
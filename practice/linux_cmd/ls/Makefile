CC = gcc

all: my_ls

my_ls: my_ls.o
	$(CC) my_ls.o -o my_ls

my_ls.o: my_ls.c
	$(CC) -Wall -c my_ls.c

clean:
	rm -rf *.o
	rm -rf my_ls
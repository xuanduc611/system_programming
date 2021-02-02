CC = gcc

all: my_mv

my_mv: my_mv.o
	$(CC) my_mv.o -o my_mv

my_mv.o: my_mv.c 
	$(CC) -Wall -c my_mv.c

clean:
	rm -rf *.o
	rm -rf my_mv
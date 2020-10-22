CC = gcc
CFLAGS = -I

all: main

main: main.o my_lib.o
	$(CC) main.o my_lib.o -o main

debug: my_lib.o dbg.o
	$(CC) dbg.o my_lib.o -o dbg

my_lib.o: my_lib.c
	$(CC) -Wall -c my_lib.c

dbg.o: dbg.c
	$(CC) -Wall -c dbg.c

main.o: main.c
	$(CC) -Wall -c main.c

clean:
	rm -rf *.o
	rm -rf main

clean-debug:
	rm -rf *.o
	rm -rf dbg

CC = gcc
CFLAGS = -I

all: multi_thread

# Generate output and link object files
multi_thread: multi_thread.o
	$(CC) multi_thread.o -pthread -o multi_thread

# Generate object files without linking
multi_thread.o: multi_thread.c
	$(CC) -Wall -c multi_thread.c

clean: 
	rm -rf *.o *.out
	rm -rf multi_thread

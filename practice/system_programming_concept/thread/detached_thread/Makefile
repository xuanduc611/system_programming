CC = gcc
CFLAGS = -I

all: detached_thread

# Generate output and link object files
detached_thread: detached_thread.o
	$(CC) detached_thread.o -pthread -o detached_thread

# Generate object files without linking
detached_thread.o: detached_thread.c
	$(CC) -Wall -c detached_thread.c

clean:
	rm -rf *.o *.out
	rm -rf detached_thread

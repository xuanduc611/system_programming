CC = gcc
CFLAGS = -I

all: sample_thread

# Generate output and link object files
sample_thread: sample_thread.o
	$(CC) sample_thread.o -pthread -o sample_thread

# Generate object files without linking
sample_thread.o: sample_thread.c
	$(CC) -Wall -c sample_thread.c

clean:
	rm -rf *.o *.out
	rm -rf sample_thread

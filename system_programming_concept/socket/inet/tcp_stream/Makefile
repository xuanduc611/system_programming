CC = gcc
CFLAGS = -I
RM = rm -rf
DEP = tcp_stream_hdr.h

# Object files depend on c file and DEP
%.o: %.c $(DEP)

all : tcp_svr tcp_cli

# Generate output and link object files
tcp_svr: tcp_svr.o
	$(CC) tcp_svr.o -pthread -o tcp_svr
tcp_cli: tcp_cli.o
	$(CC) tcp_cli.o -o tcp_cli

# Generate object files without linking
tcp_svr.o: tcp_svr.c
	$(CC) -Wall -c tcp_svr.c
tcp_cli.o: tcp_cli.c
	$(CC) -Wall -c tcp_cli.c

clean:
	$(RM) *.o *.out
	$(RM) tcp_svr tcp_cli

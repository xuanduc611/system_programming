CC = gcc
CFLAGS = -I
RM = rm -rf
DEP = u_hdr.h

# Object files depend on c file and DEP
%.o: %.c $(DEP)

all : u_svr u_cli

# Generate output and link object files
u_svr: u_svr.o
	$(CC) u_svr.o -o u_svr

u_cli: u_cli.o
	$(CC) u_cli.o -o u_cli

# Generate object files without linking
u_svr.o: u_svr.c
	$(CC) -Wall -c u_svr.c

u_cli.o: u_cli.c
	$(CC) -Wall -c u_cli.c

clean:
	$(RM) *.o *.out
	$(RM) u_svr u_cli


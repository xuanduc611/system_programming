CC = gcc
CFLAGS = -I
RM = rm -rf
DEP = urd_hdr.h

# Object files depend on c file and DEP
%.o: %.c $(DEP)

all : urd_svr urd_cli
	if [ -d /tmp/dxduc ] ; then \
		echo "/tmp/dxduc existed"; \
	else \
		echo "Create /tmp/dxduc"; \
		mkdir -p /tmp/dxduc; \
	fi;

# Generate output and link object files
urd_svr: urd_svr.o
	$(CC) urd_svr.o -pthread -o urd_svr

urd_cli: urd_cli.o
	$(CC) urd_cli.o -o urd_cli

# Generate object files without linking
urd_svr.o: urd_svr.c
	$(CC) -Wall -c urd_svr.c
urd_cli.o: urd_cli.c
	$(CC) -Wall -c urd_cli.c

clean:
	$(RM) *.o *.out
	$(RM) urd_svr urd_cli
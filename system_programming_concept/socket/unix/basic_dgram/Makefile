CC = gcc
CFLAGS = -I
RM = rm -rf
DEP = ud_hdr.h

# Object files depend on c file and DEP
%.o: %.c $(DEP)

all : ud_svr ud_cli
	if [ -d /tmp/dxduc ] ; then \
		echo "/tmp/dxduc existed"; \
	else \
		echo "Create /tmp/dxduc"; \
		mkdir -p /tmp/dxduc; \
	fi;

# Generate output and link object files
ud_svr: ud_svr.o
	$(CC) ud_svr.o -o ud_svr

ud_cli: ud_cli.o
	$(CC) ud_cli.o -o ud_cli

# Generate object files without linking
ud_svr.o: ud_svr.c
	$(CC) -Wall -c ud_svr.c

ud_cli.o: ud_cli.c
	$(CC) -Wall -c ud_cli.c

clean:
	$(RM) *.o *.out
	$(RM) ud_svr ud_cli


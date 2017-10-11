cc = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = structure_tests

HDRS = structures/structures.h

SRCS = structure_tests.c structures/structures.c

OBJS = $(SRCS:.c=.o)

$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
	
$(OBJS): $(HDRS) Makefile

clean:
	rm -f core $(EXR) *.o
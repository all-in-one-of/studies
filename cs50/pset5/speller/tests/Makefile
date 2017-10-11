cc = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = test

HDRS = ../dictionary.h ../trie.h

SRCS = test.c ../dictionary.c ../trie.c

OBJS = $(SRCS:.c=.o)

$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
	
$(OBJS): $(HDRS) Makefile

clean:
	rm -f core $(EXR) *.o
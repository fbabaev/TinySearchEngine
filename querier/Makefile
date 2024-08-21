# Makefile for Querier
#
# Firdavskhon Babaev, May 2024

# Compiler options
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50 -I../indexer

# Paths to libraries and includes
LIBCS50 = ../libcs50/libcs50-given.a
COMMON = ../common/common.a

# Executable target
TARGETS = querier

# Source files
SRCS = querier.c

# Object files generated from source files
OBJS = $(SRCS:.c=.o)

# Build all target executables
all: $(TARGETS)

querier: querier.o $(COMMON) $(LIBCS50)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGETS)

# Run tests using testing script
.PHONY: test
test:
	chmod +x testing.sh
	./testing.sh > testing.out 2>&1

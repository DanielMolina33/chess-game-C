# Define the target for the default build
all: main

# Compiler and flags
CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm -Iinclude

# Source and header files
SRCS = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)

# Main target that compiles the source files
main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

# Debug target that compiles with no optimization
main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

# Clean target to remove generated files
clean:
	rm -f main main-debug

# Phony targets to avoid conflicts with files
.PHONY: all clean main main-debug

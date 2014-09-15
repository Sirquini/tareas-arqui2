# Compiler to use
CC=clang++

# Compiler flags
CFLAGS=-Wall -std=c++11

all: translator

translator: translator.cpp
	$(CC) $(CFLAGS) translator.cpp -o translator

clean:
	rm -rf translator

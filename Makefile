
U_NAME_S=$(shell uname -s)
CC = gcc

CFLAGS = -std=c11 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CLIBS = -Ilibs/

SRC= $(wildcard src/*.c)


all:
	$(CC) -g $(SRC) $(CFLAGS) $(CLIBS) -o main.exe
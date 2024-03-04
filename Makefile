
compile_srcs := src/
lib_files := lib/
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CFLAGS_DEBUG = ${CFLAGS} -g -O0 -fno-builtin

main: src/main.c	
	${GCC} ${compile_srcs}main.c ${CFLAGS} -o build/main -I${lib_files}


CC=gcc
CFLAGS=-Wall -lm

main: main.o ppm.o
	$(CC) main.o ppm.o -o main.out
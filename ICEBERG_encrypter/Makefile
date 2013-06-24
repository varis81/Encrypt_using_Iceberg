#
#Makefile for Iceberg
#

all: main iceberg

main: main.c
	gcc -o main main.c

iceberg: iceberg.c
	gcc -o iceberg iceberg.c -lm

clean:
	rm -f main iceberg *.o

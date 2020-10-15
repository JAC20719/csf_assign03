#
# Makefile for CSF Assignment 3
# 

CC=g++ 
CFLAGS =-std=c++11 -Wall -Wextra -pedantic -g

all : file1

file1 : file1.o file2.o
	 $(CC) -o file1 file1.o file2.o

file1.o : file1.cpp file1.h
	$(CC) $(CFLAGS) -c file1.cpp file1.h

clean :
	rm -f *.o file1


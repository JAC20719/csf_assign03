#
# Makefile for CSF Assignment 3
# 

CC=g++ 
CFLAGS =-std=c++11 -Wall -Wextra -pedantic -g

csim : csim.o cache.o set.o block.o
	 $(CC) -o csim csim.o cache.o set.o block.o

csim.o : csim.cpp cache.h 
	$(CC) $(CFLAGS) -c csim.cpp 

cache.o : cache.cpp cache.h set.h
	$(CC) $(CFLAGS) -c cache.cpp

set.o : set.cpp set.h block.h
	$(CC) $(CFLAGS) -c set.cpp

block.o : block.cpp block.h
	$(CC) $(CFLAGS) -c block.cpp

clean :
	rm -f *.o file1


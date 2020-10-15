#
# Makefile for CSF Assignment 3
# 

CC=g++ 
CFLAGS =-std=c++11 -Wall -Wextra -pedantic -g

csim : csim.o
	 $(CC) -o csim csim.o

csim.o : csim.cpp
	$(CC) $(CFLAGS) -c csim.cpp

clean :
	rm -f *.o file1


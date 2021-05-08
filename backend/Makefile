
CC = g++
CFLAGS = -std=c++17

main: psys.cpp psys.o psys.hpp
	$(CC) $(CFLAGS) main.cpp psys.o -o main

psys.o: psys.cpp psys.hpp
	$(CC) $(CFLAGS) -c psys.cpp



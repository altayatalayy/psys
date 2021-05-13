
CC = g++
CFLAGS = -std=c++17

main.out: main.cpp psys.cpp psys.o psys.hpp psyspy.cpp
	$(CC) $(CFLAGS) main.cpp psys.o -o main.out
	./compile_pybind.sh psyspy.cpp psyspy

psys.o: psys.cpp psys.hpp
	$(CC) $(CFLAGS) -c psys.cpp



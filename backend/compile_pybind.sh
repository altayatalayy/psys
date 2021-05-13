#!/bin/bash
gcc -std=c++17 $(python3.9 -m pybind11 --includes) -shared $1 psys.o -o $2$(python3.9-config --extension-suffix) -lstdc++ -undefined dynamic_lookup $(python3.9-config --ldflags)

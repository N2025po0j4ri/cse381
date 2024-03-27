#!/bin/bash

g++ -std=c++17 -g -Wall -O3 -o chomper1 chomper1.cpp
g++ -std=c++17 -g -Wall -O3 -o chomper2 chomper2.cpp
g++ -std=c++17 -g -Wall -O3 -o chomper4 chomper4.cpp

/usr/bin/time -v ls -lR chomper1 chomper2 chomper4 ~/ >> /dev/null
timing.dat 2>> /dev/null
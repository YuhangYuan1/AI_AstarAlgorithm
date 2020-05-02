#!/bin/bash

echo "Compiling..."

g++ -c aStar.cpp -o aStar.o
g++ -c Puzzle.cpp -o Puzzle.o
g++ aStar.o Puzzle.o -o aStar

echo "Compiling Finished!" 

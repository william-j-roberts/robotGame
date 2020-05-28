# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o material.o worldGen.o
	$(CXX) $(CXXFLAGS) -o main main.o material.o worldGen.o

# The main.o target can be written more simply

main.o: main.cpp material.h worldGen.h
	$(CXX) $(CXXFLAGS) -c main.cpp

material.o: material.h

worldGen.o: worldGen.h material.h
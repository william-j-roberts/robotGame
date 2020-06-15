CXX = g++
CXXFLAGS = -Wall -g
NCFLAG = -lncurses

main: main.o material.o worldGen.o
	$(CXX) $(CXXFLAGS) -o main main.o material.o worldGen.o $(NCFLAG)

main.o: main.cpp material.h worldGen.h colorDefinitions.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(NCFLAG)

material.o: material.h colorDefinitions.h

worldGen.o: worldGen.h material.h colorDefinitions.h direction.h

clean:
	rm *.o main
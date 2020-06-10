#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "material.h"
using namespace std;

#ifndef WORLDGEN_H
#define WORLDGEN_H

class World{
public:
    World(int sz, string matBase, int xCoord, int yCoord);
    World(int sz, string matBase, string matAdd, double rate, bool clumping, string matAdd2, double rate2, bool clumping2, string matAdd3, double rate3, bool clumping3, int xCoord, int yCoord);
    World(string worldTemplate, int sz, int xCoord, int yCoord);
    void timeToDeallocate();
    int nearbyMat(string mat, int x, int y);
    void sprinkle(string mat, double intensity, bool clumping);
    //void treeGen(double intensity, bool clumping);
    void mountainGen(int numRanges, int size);
    void riverGen(string mat);
    pair <int, int> getCoords();
    int getSize();
    void displayMap(WINDOW * win);

protected:
    //string ** map;
    Material** map;
    string materialBase, materialAdd, materialAdd2, materialAdd3;
    int size;
    pair <int, int> coords;

};

#endif //WORLDGEN_H
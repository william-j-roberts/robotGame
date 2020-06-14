#include "material.h"
#include "materialType.h"

#ifndef WORLDGEN_H
#define WORLDGEN_H

class World{
public:
    World(int sz, materialType matBase, int xCoord, int yCoord);
    World(int sz, materialType matBase, materialType matAdd, double rate, bool clumping, materialType matAdd2, double rate2, bool clumping2, materialType matAdd3, double rate3, bool clumping3, int xCoord, int yCoord);
    World(std::string worldTemplate, int sz, int xCoord, int yCoord);
    void timeToDeallocate();
    int nearbyMat(materialType mat, int x, int y);
    void sprinkle(materialType mat, double intensity, bool clumping);
    //void treeGen(double intensity, bool clumping);
    void mountainGen(int numRanges, int size);
    void riverGen(materialType mat);
    std::pair <int, int> getCoords();
    int getSize();
    WINDOW * displayMap(int startX, int startY);

protected:
    Material** map;
    materialType materialBase, materialAdd, materialAdd2, materialAdd3;
    int size;
    std::pair <int, int> coords;

};

#endif //WORLDGEN_H
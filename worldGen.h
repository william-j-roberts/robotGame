#include "material.h"
#include "materialType.h"

#ifndef WORLDGEN_H
#define WORLDGEN_H

class World{
public:
    World(int len, int wid, int xCoord, int yCoord, bool isStatic, materialType matBase);
    World(int len, int wid, int xCoord, int yCoord, bool isStatic, materialType matBase, materialType matAdd, double rate, bool clumping, materialType matAdd2, double rate2, bool clumping2, materialType matAdd3, double rate3, bool clumping3);
    World(std::string worldTemplate, int len, int wid, int xCoord, int yCoord, bool isStatic);
    void timeToDeallocate();
    int nearbyMat(materialType mat, int x, int y);
    void sprinkle(materialType mat, double intensity, bool clumping);
    //void treeGen(double intensity, bool clumping);
    void mountainGen(int numRanges, int size);
    void riverGen(materialType mat);
    std::pair <int, int> getCoords();
    int getLength();
    int getWidth();
    bool checkIfStatic();
    WINDOW * displayStaticMap(int startX, int startY);

protected:
    Material** map;
    materialType materialBase, materialAdd, materialAdd2, materialAdd3;
    int length, width;
    std::pair <int, int> coords;
    bool staticMap;

};

#endif //WORLDGEN_H
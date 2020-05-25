#include <iostream>
using namespace std;

#ifndef MATERIAL_H
#define MATERIAL_H

class Material{
public:
    Material();
    Material(string type);
    string getType();
    void setType(string type);
    char getGraphic();
    string getColor();
protected:
    string matType;
    char graphic;
    string color;
    bool hidden;
    bool occupiedByPlayer;
};

#endif //MATERIAL_H
#include <ncurses.h>
#include "materialType.h"

#ifndef MATERIAL_H
#define MATERIAL_H

class Material{
public:
    Material();
    Material(materialType type);
    materialType getType();
    void setType(materialType type);
    char getGraphic();
    int getColor();
    void explore();
    void occupy();
    void leave();
protected:
    materialType matType;
    char graphic;
    int color;
    bool hidden;
    bool occupiedByPlayer;
};

#endif //MATERIAL_H
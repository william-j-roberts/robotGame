#include <iostream>
#include "material.h"
#include "colorDefinitions.h"
using namespace std;

Material::Material(){
    this->setType(undecided);
    hidden = true;
    occupiedByPlayer = false;
}

Material::Material(materialType type){
    this->setType(type);
    hidden = true;
    occupiedByPlayer = false;
    
}

materialType Material::getType(){
    return matType;
}

void Material::setType(materialType type){
    matType = type;
    switch(type){
        case undecided:
            graphic = 'X';
            color = PAIR_TERMINAL;
            break; 
        case test:
            graphic = '$';
            color = PAIR_TERMINAL;
        case nothing:
            graphic = ' ';
            color = PAIR_TERMINAL;
            break;
        case rock:
            graphic = '_';
            color = PAIR_ROCK;
            break;
        case grass:
            graphic = ' ';
            color = PAIR_GRASS;
            break;
        case water:
            graphic = '~';
            color = PAIR_WATER;
            break;
        case tree:
            graphic = '^';
            color = PAIR_TREE;
            break;
        case sand:
            graphic = '.';
            color = PAIR_SAND;
            break;
        case mountain:
            graphic = '\\';
            color = PAIR_ROCK;
            break;
        case mountain_peak:
            graphic = 'A';
            color = PAIR_TERMINAL;
            break;
        case town:
            graphic = '#';
            color = PAIR_SAND;
            break;
        case hole:
            graphic = ' ';
            color = PAIR_TERMINAL;
            break;
        case null:
            graphic = 'N';
            color = PAIR_TERMINAL;
        default:
            cout << "error! materialType does not exist" << endl;
    }
}

char Material::getGraphic(){
    return graphic;
}

int Material::getColor(){
    return color;
}

void Material::explore(){

}

void Material::occupy(){

}

void Material::leave(){

}
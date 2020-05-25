#include <iostream>
#include "material.h"
using namespace std;

const string BLACK = "\033[0;30m";
const string RED = "\033[0;31m";
const string GREEN = "\033[0;32m";
const string BRORANGE = "\033[0;33m";
const string BLUE = "\033[0;34m";
const string PURPLE = "\033[0;35m";
const string CYAN = "\033[0;36m";
const string LIGHT_GRAY = "\033[0;37m";
const string DARK_GRAY = "\033[1;30m";
const string LIGHT_RED = "\033[1;31m";
const string LIGHT_GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string LIGHT_BLUE = "\033[1;34m";
const string LIGHT_PURPLE = "\033[1;35m";
const string LIGHT_CYAN = "\033[1;36m";
const string WHITE = "\033[1;37m";
const string NC = "\033[1m"; //No Color

Material::Material(){
    this->setType("undecided");
    hidden = true;
    occupiedByPlayer = false;
}

Material::Material(string type){
    this->setType(type);
    hidden = true;
    occupiedByPlayer = false;
    
}

string Material::getType(){
    return matType;
}

void Material::setType(string type){
    matType = type;
    if(type == "undecided"){
        graphic = 'X';
        color = WHITE; 
    }else if(type == "nothing"){
        graphic = ' ';
        color = NC;
    }else if(type == "rock"){
        graphic = '_';
        color = DARK_GRAY;
    }else if(type == "grass"){
        graphic = ' ';
        color = LIGHT_GREEN;
    }else if(type == "water"){
        graphic = '~';
        color = LIGHT_BLUE;
    }else if(type == "tree"){
        graphic = '^';
        color = GREEN;
    }else if(type == "sand"){
        graphic = '.';
        color = YELLOW;
    }else if(type == "mountain"){
        graphic = '\\';
        color = DARK_GRAY; //white?
    }else if(type == "mountain-peak"){
        graphic = 'A';
        color = WHITE;
    }else if(type == "town"){
        graphic = '#';
        color = BRORANGE;
    }else if(type == "hole"){
        graphic = ' ';
        color = NC;
    }else{
        graphic = '$';
        color = LIGHT_CYAN;
    }
}

char Material::getGraphic(){
    return graphic;
}

string Material::getColor(){
    return color;
}
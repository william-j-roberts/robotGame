#include <iostream>
#include "worldGen.h"
#include "material.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const string NC = "\033[1m"; //No Color

//FOR GENERATING PLAIN WORLD WITH ONE MATERIAL
//SZ refers to length/width of square grid
//MATBASE refers to base material of world
//XCOORD & YCOORD refer to x and y position of world
World::World(int sz, string matBase, int xCoord, int yCoord){
    size = sz;
    coords = make_pair(xCoord, yCoord);
    materialBase = matBase;
    materialAdd = "null";
    materialAdd2 = "NULL";
    materialAdd3 = "NULL";
    map = new Material*[sz];
    for(int i = 0; i < sz; i++)
        map[i] = new Material[sz];
    for(int i = 0; i < sz; i++)
        for(int j = 0; j < sz; j++)
            map[i][j] = Material(matBase);
}

//FOR GENERATING WORLD WITH 1-4 MATERIALS
//MATADD refers to supplementary material to be added to world
//RATE refers to frequency of material being added
//CLUMPING refers to if material occurs more often in clusters
World::World(int sz, string matBase, string matAdd, double rate, bool clumping, string matAdd2, double rate2, bool clumping2, string matAdd3, double rate3, bool clumping3, int xCoord, int yCoord){
    size = sz;
    coords = make_pair(xCoord, yCoord);
    materialBase = matBase;
    materialAdd = matAdd;
    materialAdd2 = matAdd2;
    materialAdd3 = matAdd3;

    map = new Material*[sz];
    for(int i = 0; i < sz; i++)
        map[i] = new Material[sz];
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            map[i][j] = Material(matBase);
        }
    }

    /*
    map = new string*[sz];
    for(int i = 0; i < sz; i++)
        map[i] = new string[sz];
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            map[i][j] = matBase;
        }
    }*/

    this->sprinkle(matAdd, rate, clumping);
    if(rate2 > 0)
        this->sprinkle(matAdd2, rate2, clumping2);
    if(rate3 > 0)
        this->sprinkle(matAdd3, rate3, clumping3);
}

World::World(string worldTemplate, int sz, int xCoord, int yCoord){
    size = sz;
    coords = make_pair(xCoord, yCoord);
    materialBase = "grass";
    materialAdd = "water";
    materialAdd2 = "tree";
    materialAdd3 = "blah";
    map = new Material*[sz];
        for(int i = 0; i < sz; i++)
            map[i] = new Material[sz];

    if(worldTemplate == "standard"){
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                map[i][j] = Material("grass"); //or nothing? or make grass have blank symbol?
        this->sprinkle("water", 0.04, true);
        this->sprinkle("tree", 0.05, true);

    //World newWorld(40, "nothing", "tree", 0.055, true, "water", 0.035, true, "nothing", 0.0, true, 0, 0);
    }else if(worldTemplate == "forest"){
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                map[i][j] = Material("grass"); //or nothing? or make grass have blank symbol?
        this->sprinkle("water", 0.035, true);
        this->sprinkle("tree", 0.045, true);
    }else{
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                map[i][j] = Material("grass"); //or nothing? or make grass have blank symbol?
        this->sprinkle("water", 0.035, true);
        this->sprinkle("tree", 0.045, true);
    }
}

void World::timeToDeallocate(){
    for(int i=0; i<size; i++)
        delete[] map[i];
    delete[] map;
}

//CHECKS IF SURROUNDING SPACES CONTAIN SAME MATERIAL, EACH ADDITIONAL NEARBY MATERIAL INCREASES MULTIPLIER
int World::nearbyMat(string mat, int x, int y){
    int multiplier = 1;
    if(x > 0 && x < (size - 1) && y > 0 && y < (size - 1)){
        for(int j = y - 1; j <= y + 1; j++){
            for(int i = x - 1; i <= x + 1; i++){
                if(map[i][j].getType() == mat)
                    multiplier += 4;
            }
        }
    }/*
    else if(x > 0 && x < (size - 1) && y > 0){

    }
    else if(x > 0 && x < (size - 1) && y < (size - 1)){

    }
    else if(x > 0 && y > 0 && y < (size - 1)){

    }
    else if(x < (size - 1) && y > 0 && y < (size - 1)){

    }*/
    //todo, might not tho
    return multiplier;
}

//SPRINKLES MATERIAL THROUGHOUT MAP ACCORDING TO SPECIFIED INTENSITY, CAN CHOOSE TO HAVE THEM OCCUR IN CLUMPS OR NOT
//MAT refers to new material being inserted throughout map
//INTENSITY refers to frequency of new material
//CLUMPING refers to if material is more likely to occur if same material exists in neighboring spots
//      NOTE: clumping will usually dominate most of the map when material intensity is > ~0.04
void World::sprinkle(string mat, double intensity, bool clumping){
    //srand(time(NULL));
    int chance = 1000 * intensity;
    
    if(clumping){
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++)
                if((rand() % 1000 + 1) <= chance * nearbyMat(mat, i, j))
                    map[i][j].setType(mat);
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if((rand() % 1000 + 1) <= chance)
                    map[i][j].setType(mat);
            }
        }
    }
}

//TODO: add a check so that mountain ranges generate away from eachother
void World::mountainGen(int numRanges, int mtnSize){
    pair<int, int> peak;

    for(int i=0; i<numRanges; i++){
        peak.first = rand() % size;
        peak.second = rand() % size;
        map[peak.first][peak.second].setType("mountain-peak");
    }
}

void World::riverGen(string mat){

}

//RETURNS POSITION OF WORLD
pair <int, int> World::getCoords(){
    return coords;
}

//RETURNS SIZE (WIDTH) OF WORLD
int World::getSize(){
    return size;
}

//DISPLAYS WORLD
void World::displayMap(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            cout << map[i][j].getColor() << map[i][j].getGraphic() << NC << " ";
        cout << endl;
    }

    /* FOR WIDER SPACING
        for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            cout << map[i][j] << "   ";
        cout << endl;
        cout << endl;
    }*/
}
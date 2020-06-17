#include <iostream>
#include <ncurses.h>
#include "worldGen.h"
#include "material.h"
#include "materialType.h"
#include "direction.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//FOR GENERATING PLAIN WORLD WITH ONE MATERIAL
//SZ refers to length/width of square grid
//MATBASE refers to base material of world
//XCOORD & YCOORD refer to x and y position of world
World::World(int len, int wid, int xCoord, int yCoord, bool isStatic, materialType matBase){
    length = len;
    width = wid;
    coords = make_pair(xCoord, yCoord);
    staticMap = isStatic;
    materialBase = matBase;
    materialAdd = null;
    materialAdd2 = null;
    materialAdd3 = null;
    map = new Material*[wid];
    for(int i = 0; i < wid; i++)
        map[i] = new Material[len];
    for(int i = 0; i < wid; i++)
        for(int j = 0; j < len; j++)
            map[i][j] = Material(matBase);
}

//FOR GENERATING WORLD WITH 1-4 MATERIALS
//MATADD refers to supplementary material to be added to world
//RATE refers to frequency of material being added
//CLUMPING refers to if material occurs more often in clusters
World::World(int len, int wid, int xCoord, int yCoord, bool isStatic, materialType matBase, materialType matAdd, double rate, bool clumping, materialType matAdd2, double rate2, bool clumping2, materialType matAdd3, double rate3, bool clumping3){
    length = len;
    width = wid;
    coords = make_pair(xCoord, yCoord);
    staticMap = isStatic;
    materialBase = matBase;
    materialAdd = matAdd;
    materialAdd2 = matAdd2;
    materialAdd3 = matAdd3;

    map = new Material*[wid];
    for(int i = 0; i < wid; i++)
        map[i] = new Material[len];
    for(int i = 0; i < wid; i++){
        for(int j = 0; j < len; j++){
            map[i][j] = Material(matBase);
        }
    }

    this->sprinkle(matAdd, rate, clumping);
    if(rate2 > 0)
        this->sprinkle(matAdd2, rate2, clumping2);
    if(rate3 > 0)
        this->sprinkle(matAdd3, rate3, clumping3);

    map[0][0] = Material(test);
    map[1][1] = Material(test);
    map[2][2] = Material(test);
    map[wid - 1][len - 1] = Material(test);
}

World::World(std::string worldTemplate, int len, int wid, int xCoord, int yCoord, bool isStatic){
    length = len;
    width = wid;
    coords = make_pair(xCoord, yCoord);
    staticMap = isStatic;
    materialBase = grass;
    materialAdd = water;
    materialAdd2 = tree;
    materialAdd3 = null;
    map = new Material*[wid];
    for(int i = 0; i < wid; i++)
        map[i] = new Material[len];

    if(worldTemplate == "standard"){
        for(int i = 0; i < wid; i++)
            for(int j = 0; j < len; j++)
                map[i][j] = Material(grass); //or nothing? or make grass have blank symbol?
        this->sprinkle(water, 0.04, true);
        this->sprinkle(tree, 0.05, true);

    //World newWorld(40, "nothing", "tree", 0.055, true, "water", 0.035, true, "nothing", 0.0, true, 0, 0);
    }else if(worldTemplate == "forest"){
        for(int i = 0; i < wid; i++)
            for(int j = 0; j < len; j++)
                map[i][j] = Material(grass); //or nothing? or make grass have blank symbol?
        this->sprinkle(water, 0.035, true);
        this->sprinkle(tree, 0.045, true);
    }else{
        for(int i = 0; i < wid; i++)
            for(int j = 0; j < len; j++)
                map[i][j] = Material(grass); //or nothing? or make grass have blank symbol?
        this->sprinkle(water, 0.035, true);
        this->sprinkle(tree, 0.045, true);
    }
}

void World::timeToDeallocate(){
    for(int i=0; i<width; i++)
        delete[] map[i];
    delete[] map;
}

//CHECKS IF SURROUNDING SPACES CONTAIN SAME MATERIAL, EACH ADDITIONAL NEARBY MATERIAL INCREASES MULTIPLIER
int World::nearbyMat(materialType mat, int x, int y){
    int multiplier = 1;
    if(x > 0 && x < (width - 1) && y > 0 && y < (length - 1)){
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
void World::sprinkle(materialType mat, double intensity, bool clumping){
    int chance = 1000 * intensity;
    
    if(clumping){
        for(int i=0; i<width; i++){
            for(int j=0; j<length; j++)
                if((rand() % 1000 + 1) <= chance * nearbyMat(mat, i, j))
                    map[i][j].setType(mat);
        }
    }else{
        for(int i=0; i<width; i++){
            for(int j=0; j<length; j++){
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
        peak.first = rand() % ((width + length) / 2);
        peak.second = rand() % ((width + length) / 2);
        map[peak.first][peak.second].setType(mountain_peak);
    }
}

void World::riverGen(materialType mat){

}

//RETURNS POSITION OF WORLD
pair <int, int> World::getCoords(){
    return coords;
}

//RETURNS LENGTH OF WORLD
int World::getLength(){
    return length;
}

//RETURNS WIDTH OF WORLD
int World::getWidth(){
    return width;
}

//CHECK IF MAP IS STATIC; IF STATIC, PLAYER NAVIGATES WORLD SCREEN BY SCREEN; OTHERWISE, WORLD MOVES PAST
bool World::checkIfStatic(){
    return staticMap;
}

//DISPLAYS WORLD                         TODO: CREATE STACK/QUEUE(?) TO TRACK CHANGES FOR AN "UPDATEMAP" FUNCTION, AVOIDS GOING THRU WHOLE DISPLAYMAP LOOP ALWAYS 
WINDOW * World::displayStaticMap(int startX, int startY){
    WINDOW * tempWin;
    int winLength = length + 2;  
    int winWidth = width + 2;
    tempWin = newwin(winLength, winWidth, startX, startY);

    refresh();

    //create border around map
    box(tempWin, 0, 0);

    //draw map
    for(int i = 0; i < width; i++){
        for(int j = 0; j < length; j++){
            wattron(tempWin, COLOR_PAIR(map[i][j].getColor()));
            mvwaddch(tempWin, j + 1, i + 1, map[i][j].getGraphic());
            wattroff(tempWin, COLOR_PAIR(map[i][j].getColor()));
        }
    }
   
    wrefresh(tempWin);
    return tempWin;
}
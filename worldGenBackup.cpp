#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class World{
public:
World(int sz, string matBase, int xCoord, int yCoord);
World(int sz, string matBase, string matAdd, double rate, bool clumping, string matAdd2, double rate2, bool clumping2, string matAdd3, double rate3, bool clumping3, int xCoord, int yCoord);
int nearbyMat(string mat, int x, int y);
void sprinkle(string mat, double intensity, bool clumping);
//void treeGen(double intensity, bool clumping);
void mountainGen(int numRanges);
void riverGen(string mat);
pair <int, int> getCoords();
int getSize();
void displayMap();

protected:
string ** map;
string materialBase, materialAdd, materialAdd2, materialAdd3;
int size;
pair <int, int> coords;

};

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
    map = new string*[sz];
    for(int i = 0; i < sz; i++)
        map[i] = new string[sz];
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            map[i][j] = matBase;
        }
    }
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

    map = new string*[sz];
    for(int i = 0; i < sz; i++)
        map[i] = new string[sz];
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            map[i][j] = matBase;
        }
    }

    this->sprinkle(matAdd, rate, clumping);
    if(rate2 > 0)
        this->sprinkle(matAdd2, rate2, clumping2);
    if(rate3 > 0)
        this->sprinkle(matAdd3, rate3, clumping3);
}

//CHECKS IF SURROUNDING SPACES CONTAIN SAME MATERIAL, EACH ADDITIONAL NEARBY MATERIAL INCREASES MULTIPLIER
int World::nearbyMat(string mat, int x, int y){
    int multiplier = 1;
    if(x > 0 && x < (size - 1) && y > 0 && y < (size - 1)){
        for(int j = y - 1; j <= y + 1; j++){
            for(int i = x - 1; i <= x + 1; i++){
                if(map[i][j] == mat)
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
    srand(time(NULL));
    int chance = 1000 * intensity;
    
    if(clumping){
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++)
                if((rand() % 1000 + 1) <= chance * nearbyMat(mat, i, j))
                    map[i][j] = mat;
        }
    }else{
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if((rand() % 1000 + 1) <= chance)
                    map[i][j] = mat;
            }
        }
    }
}

void World::mountainGen(int numRanges){
    srand(time(NULL));

    
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
            cout << map[i][j] << " ";
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

int main(){
    World newWorld(30, " ", "@", 0.06, true, ".", 0.04, false, "^", 0.035, true, 0, 0);
    cout << "newWorld is a " << newWorld.getSize() << "x" << newWorld.getSize() << " map." << endl;
    cout << endl;
    newWorld.displayMap();
}
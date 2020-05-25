#include <iostream>
#include "worldGen.h"
#include "material.h"
using namespace std;

/*
Black        0;30     Dark Gray     1;30
Red          0;31     Light Red     1;31
Green        0;32     Light Green   1;32
Brown/Orange 0;33     Yellow        1;33
Blue         0;34     Light Blue    1;34
Purple       0;35     Light Purple  1;35
Cyan         0;36     Light Cyan    1;36
Light Gray   0;37     White         1;37

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
const string NC = "\033[1m"; //No Color*/

int main(){
    srand((unsigned)time(0));
    //World newWorld(40, "nothing", "tree", 0.055, true, "water", 0.035, true, "nothing", 0.0, true, 0, 0);
    World newWorld("standard", 65, 0, 0);
    cout << "newWorld is a " << newWorld.getSize() << "x" << newWorld.getSize() << " map." << endl;
    cout << endl;
    newWorld.displayMap();
    /*
    cout << endl;
    cout << endl;
    newWorld.mountainGen(12, 1);
    newWorld.displayMap();*/

    newWorld.timeToDeallocate();

    return 0;
}
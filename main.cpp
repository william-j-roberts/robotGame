#include <iostream>
#include <ncurses.h>
#include "worldGen.h"
#include "material.h"
#include "colorDefinitions.h"
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

/*
COLOR_BLACK
COLOR_RED
COLOR_GREEN
COLOR_YELLOW
COLOR_BLUE
COLOR_MAGENTA
COLOR_CYAN
COLOR_WHITE
*/

void makeColors(){
    init_pair(PAIR_TERMINAL, COLOR_WHITE, COLOR_BLACK);
    init_pair(PAIR_PLAYER, COLOR_BLACK, COLOR_WHITE);
    init_pair(PAIR_GRASS, COLOR_YELLOW, COLOR_GREEN);
    init_pair(PAIR_WATER, COLOR_WHITE, COLOR_BLUE);
    init_pair(PAIR_TREE, COLOR_GREEN, COLOR_BLACK);
    init_pair(PAIR_SAND, COLOR_BLACK, COLOR_YELLOW);
    init_pair(PAIR_ROCK, COLOR_BLACK, COLOR_WHITE);
}

void userInput(){

}

int main(){
    srand((unsigned)time(0));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE) {
        endwin();
        cout << "Error: terminal does not support color" << endl;
    }else{
        start_color();
        makeColors();
        
        WINDOW * win;
        WINDOW * win2;

        //int numCols = COLS - 1;
        //int numRows = LINES - 1;

        World newWorld(40, "nothing", "tree", 0.055, true, "water", 0.035, false, "nothing", 0.0, false, 0, 0);
        newWorld.displayMap(win, 0, 0);
        newWorld.displayMap(win2, 0, 45);

        endwin();
        newWorld.timeToDeallocate();
    }

    return 0;
}
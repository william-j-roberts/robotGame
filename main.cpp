#include <iostream>
#include <stdlib.h>
#include "worldGen.h"
#include "colorDefinitions.h"
using namespace std;

// COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE

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

        World newWorld(40, nothing, tree, 0.055, true, water, 0.035, false, nothing, 0.0, false, 0, 0);
        newWorld.displayMap(win, 0, 0);
        newWorld.displayMap(win2, 0, 45);

        endwin();
        newWorld.timeToDeallocate();
    }

    return 0;
}
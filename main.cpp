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

/*bool canMove(WINDOW * playerWin, int x, int y){
    if(mvwinch(playerWin, y, x) != '│' && mvwinch(playerWin, y, x) != '─')
        return true;
    return false;
}*/

void userInput(WINDOW * playerWin, int startX, int startY, int sz){
    int x = startX;
    int y = startY;
    int input;
    char * txtInput;

    do{
        mvwaddch(playerWin, y, x, '#');
        move(5 + sz + 2, 6);
        wrefresh(playerWin);

        input = getch();
        switch(input){
            case 'W':
            case 'w':
            case KEY_UP:
                if(y > 1)
                    y -= 1;
                break;
            case 'A':
            case 'a':
            case KEY_LEFT:
                if(x > 1)
                    x -= 1;
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                if(x < sz)
                    x += 1;
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                if(y < sz)
                    y += 1;
                break;
            case 'T':
            case 't':
                move(5 + sz + 2, 6);
                wrefresh(playerWin);
                echo();
                do{
                    getstr(txtInput);
                    mvaddstr(5 + sz + 2, 6, txtInput);
                    
                }while(txtInput != "move");
                noecho();
                break;
        }

    }while(input != 'q' && input != 'Q');
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
        
        //int numCols = COLS - 1;
        //int numRows = LINES - 1;

        //generate and display map
        int worldSize = 40;
        World newWorld(worldSize, nothing, tree, 0.055, true, water, 0.035, false, nothing, 0.0, false, 0, 0);
        WINDOW * win;
        win = newWorld.displayMap(5, 6);
        mvaddstr(0, 0, "Navigate with WASD or arrow keys, press q to quit");

        //allow user to navigate/interact with program
        userInput(win, 14, 14, worldSize);
        
        endwin();
        newWorld.timeToDeallocate();
    }

    return 0;
}
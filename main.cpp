#include <iostream>
#include <stdlib.h>
#include "worldGen.h"
#include "colorDefinitions.h"
using namespace std;

#define ESC 27

// COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE

void makeColors();
void userInput(WINDOW * playerWin, int startX, int startY, int len, int wid);

int main(){
    srand((unsigned)time(0));

    //setup input
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    //checking that terminal can display color
    if (has_colors() == FALSE) {
        endwin();
        cout << "Error: terminal does not support color" << endl;
    }else{
        //setup color
        start_color();
        makeColors();
        
        //int numCols = COLS - 1;
        //int numRows = LINES - 1;

        //generate and display map
        int length = 40;    //7 x 3 ratio for square map?
        int width = 93;
        World newWorld(length, width, 0, 0, true, nothing, tree, 0.055, true, water, 0.035, false, nothing, 0.0, false);
        WINDOW * win;
        win = newWorld.displayStaticMap(5, 6);
        mvaddstr(0, 0, "Navigate with WASD or arrow keys, press q to quit");

        //allow user to navigate/interact with program
        userInput(win, 14, 14, length, width);
        
        //shutdown
        endwin();
        newWorld.timeToDeallocate();
    }

    return 0;
}

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

void userInput(WINDOW * playerWin, int startX, int startY, int len, int wid){
    int x = startX;
    int y = startY;
    int input;
    char * txtInput;
    char * escapeInput = "move";

    do{
        mvwaddch(playerWin, y, x, '#');
        wmove(playerWin, y, x);
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
                if(x < wid)
                    x += 1;
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                if(y < len)
                    y += 1;
                break;
            case 'T':
            case 't':
                move(5 + len + 2, 6);
                wrefresh(playerWin);
                echo();
                do{
                    getstr(txtInput);
                    if(txtInput == escapeInput)
                        mvaddstr(6 + len + 2, 6, "yessir");
                    else
                    {
                        mvaddstr(6+ len + 2, 6, "nope");
                    }                    
                    
                }while(txtInput != "move");
                noecho();
                //wmove(playerWin, y, x);
                break;
        }

    }while(input != 'q' && input != 'Q');
}
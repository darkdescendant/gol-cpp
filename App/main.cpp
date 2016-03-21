#include <iostream>
#include <sstream>
#include <ncurses.h>

#include "GameOfLife.h"

int main(int argc, char* argv[]) {

    initscr();
    noecho();

    GameOfLife game(30,30);
    game.set_cell(3,6);
    game.set_cell(4,7);
    game.set_cell(5,5);
    game.set_cell(5,6);
    game.set_cell(5,7);

    clear();

    while (1)
    {
        game.step();
        for (int i = 0; i < game.height(); i++)
        {
            for (int j = 0; j < game.width(); j++)
            {
                char cell = game.is_cell_set(j,i) ? '*' : '.';
                mvprintw(j, i, "%c", cell);
            }
        }
        refresh();
    }

    endwin();

    return 0;
}
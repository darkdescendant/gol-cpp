//
// Created by Joseph Jones on 3/13/16.
//

#include <iostream>
#include <sstream>
#include "GameOfLife.h"

GameOfLife::GameOfLife(){
    width_ = 1;
    height_ = 1;
    board_.reset(allocate_board(width_, height_));
}

GameOfLife::GameOfLife(int w, int h){
    width_ = w;
    height_ = h;
    board_.reset(allocate_board(width_, height_));
}

std::ostream& operator<<(std::ostream& out, const GameOfLife& game)
{
    out << game.width() << "," << game.height() << std::endl;
    for (int i = 0; i < game.height(); i++)
    {
        for (int j = 0; j < game.width(); j++)
        {
            out << (game.is_cell_set(j,i) ? '*' : '.');
        }

        out << std::endl;
    }
    return out;
}


void GameOfLife::set_cell(int x, int y) {
    int cell = calculate_cell_index(x, y);
    board_[cell] = true;
}

int GameOfLife::calculate_cell_index(int x, int y) const {
    return y * width_ + x;
}

bool GameOfLife::is_cell_set(int x, int y) const {
    int cell = calculate_cell_index(x, y);
    return board_[cell];
}

void GameOfLife::clear_cell(int x, int y) {
    int cell = calculate_cell_index(x, y);
    board_[cell] = false;
}

bool * GameOfLife::allocate_board(int w, int h) {
    int size = w * h;
    bool* ret = new bool[size];
    memset(ret, 0, size * sizeof(bool));
    return ret;
}

void GameOfLife::step() {
    bool* new_board = allocate_board(width_, height_);
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            int cell = calculate_cell_index(j, i);
            if (is_cell_set(j,i))
            {
                new_board[cell] = cell_should_live(j,i);
            }
            else
            {
                new_board[cell] = cell_should_create(j,i);
            }
        }
    }

    board_.reset(new_board);
}

int GameOfLife::count_cell_neighbors(int x, int y) const {
    int count = 0;

    for (int i = std::max(y - 1, 0); i < std::min(height_, y + 2); i++)
    {
        for (int j = std::max(x - 1, 0); j < std::min(width_, x + 2); j++)
        {
            if (is_cell_set(j,i) && !(i == y && j == x))
            {
                count++;
            }
        }
    }

    return count;
}

bool GameOfLife::cell_should_live(int x, int y) const {
    return !cell_should_die(x, y);
}

bool GameOfLife::cell_should_die(int x, int y) const {
    int neighbors = count_cell_neighbors(x, y);
    return is_cell_set(x,y) && (neighbors < 2 || neighbors > 3);
}

bool GameOfLife::cell_should_create(int x, int y) const {
    int neighbors = count_cell_neighbors(x, y);
    return !is_cell_set(x,y) && neighbors == 3;
}

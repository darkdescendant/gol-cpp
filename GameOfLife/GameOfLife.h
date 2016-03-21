//
// Created by Joseph Jones on 3/13/16.
//

#ifndef GOLKATA_GAMEOFLIFE_H
#define GOLKATA_GAMEOFLIFE_H


#include <iosfwd>

class GameOfLife {
    int width_ = 0;
    int height_ = 0;

    std::unique_ptr<bool[]> board_;

    bool * allocate_board(int w, int h);

public:
    GameOfLife();
    GameOfLife(int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }

    friend std::ostream& operator<<(std::ostream& out, const GameOfLife& game);
    friend std::istream& operator>>(std::istream& in, GameOfLife& game) {
        char t;
        in >> game.width_ >> t >> game.height_;
        game.board_.reset(game.allocate_board(game.width_, game.height_));

        std::string board_line;
        int x = 0;
        int y = 0;

        while (in >> board_line)
        {
            x = 0;
            for (auto const& cell : board_line)
            {
                if (cell == '*')
                {
                    game.set_cell(x, y);
                }
                x++;
            }
            y++;
        }
        return in;
    }

    void set_cell(int x, int y);

    bool is_cell_set(int x, int y) const;

    void clear_cell(int x, int y);

    void step();

    inline int calculate_cell_index(int x, int y) const;

    int count_cell_neighbors(int x, int y) const;

    bool cell_should_live(int x, int y) const;
    bool cell_should_die(int x, int y) const;

    bool cell_should_create(int x, int y) const;
};


#endif //GOLKATA_GAMEOFLIFE_H

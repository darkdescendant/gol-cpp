#include <igloo/igloo_alt.h>
#include "GameOfLife.h"

using namespace std;
using namespace igloo;

string empty_game =
        "5,5\n"
        ".....\n"
        ".....\n"
        ".....\n"
        ".....\n"
        ".....\n";

string simple_game =
        "5,5\n"
        ".....\n"
        "..*..\n"
        ".....\n"
        ".....\n"
        ".....\n";

string simple_game_two =
        "5,5\n"
        ".....\n"
        "..*..\n"
        ".**..\n"
        ".....\n"
        ".....\n";


string simple_game_three =
        "5,5\n"
        ".....\n"
        ".**..\n"
        ".**..\n"
        ".....\n"
        ".....\n";

string simple_game_four =
        "5,5\n"
        "***..\n"
        "***..\n"
        "***..\n"
        ".....\n"
        ".....\n";

string simple_game_five =
        "5,5\n"
        "*.*..\n"
        "...*.\n"
        "*.*..\n"
        ".*...\n"
        ".....\n";

string simple_game_six =
        "5,5\n"
        ".....\n"
        ".....\n"
        "..***\n"
        "..***\n"
        "..***\n";

string simple_game_seven =
        "5,5\n"
        ".....\n"
        "...*.\n"
        "..*.*\n"
        ".*...\n"
        "..*.*\n";

string beehive =
        "6,6\n"
        "......\n"
        "..**..\n"
        ".*..*.\n"
        "..**..\n"
        "......\n"
        "......\n";


string loaf =
        "6,6\n"
        "......\n"
        "..**..\n"
        ".*..*.\n"
        "..*.*.\n"
        "...*..\n"
        "......\n";

Describe(Game_Of_Life)
{
    It(Should_take_a_width_and_a_height)
    {
        GameOfLife game(10, 10);

        Assert::That(game.width(), Equals(10));
        Assert::That(game.height(), Equals(10));
    }

    It(Should_set_a_cell)
    {
        GameOfLife game(10, 10);
        game.set_cell(5, 5);
        Assert::That(game.is_cell_set(5,5), IsTrue());
    }

    It(Should_clear_ser_cell)
    {
        GameOfLife game(10, 10);
        game.set_cell(5, 5);
        Assert::That(game.is_cell_set(5,5), IsTrue());
        game.clear_cell(5,5);
        Assert::That(game.is_cell_set(5,5), IsFalse());
    }

    It(Should_render_empty_board)
    {
        GameOfLife game(5, 5);
        ostringstream strstr_out;
        strstr_out << game;
        Assert::That(strstr_out.str(), Equals(empty_game));
    }

    It(Should_parse_game_board_width_height)
    {
        GameOfLife game;
        istringstream input(simple_game);

        input >> game;

        Assert::That(game.width(), Equals(5));
        Assert::That(game.height(), Equals(5));
    }

    It(Should_parse_game_board)
    {
        GameOfLife game;
        istringstream input(simple_game);

        input >> game;

        Assert::That(game.width(), Equals(5));
        Assert::That(game.height(), Equals(5));
        Assert::That(game.is_cell_set(2,1), IsTrue());
    }

    It(Should_round_trip_game_board)
    {
        GameOfLife game;
        istringstream input(simple_game);
        ostringstream output;

        input >> game;
        output << game;

        Assert::That(output.str(), Equals(simple_game));
    }

    It(Should_report_no_neighbors_for_cell)
    {
        GameOfLife game(5,5);
        Assert::That(game.count_cell_neighbors(1,1), Equals(0));
    }

    It(Should_report_one_neighbors_for_cell)
    {
        GameOfLife game(5,5);
        game.set_cell(0,0);
        Assert::That(game.count_cell_neighbors(1,1), Equals(1));
    }

    It(Should_report_eight_neighbors_for_cell)
    {
        GameOfLife game(5,5);
        for (int y = 1; y <= 3; y++)
        {
            for (int x = 1; x <= 3; x++)
            {
                game.set_cell(x,y);
            }
        }

        Assert::That(game.count_cell_neighbors(2,2), Equals(8));
    }

    It(Should_cell_should_die_from_lack_of_neighbors)
    {
        GameOfLife game(5,5);
        game.set_cell(2,2);
        Assert::That(game.cell_should_die(2,2), IsTrue());
    }


    It(Should_allow_cell_to_live)
    {
        GameOfLife game(5,5);
        game.set_cell(2,2);
        Assert::That(game.cell_should_die(2,2), IsTrue());
    }

    It(Should_cell_should_die_from_too_many_of_neighbors)
    {
        GameOfLife game(5,5);
        for (int y = 1; y <= 3; y++)
        {
            for (int x = 1; x <= 3; x++)
            {
                game.set_cell(x,y);
            }
        }

        Assert::That(game.cell_should_die(2,2), IsTrue());
    }

    It(Should_create_non_empty_cell_when_enough_neighbors)
    {
        GameOfLife game(5,5);
        game.set_cell(2,2);
        game.set_cell(2,3);
        game.set_cell(3,3);
        Assert::That(game.cell_should_die(3,2), IsFalse());
        Assert::That(game.cell_should_create(3,2), IsTrue());
    }

    It(Should_not_create_non_empty_cell_when_not_enough_neighbors)
    {
        GameOfLife game(5,5);
        game.set_cell(2,2);
        game.set_cell(2,3);
        Assert::That(game.cell_should_die(3,2), IsFalse());
        Assert::That(game.cell_should_create(3,2), IsFalse());
    }

    It(Should_not_create_cell_when_already_set)
    {
        GameOfLife game(5,5);
        game.set_cell(2,2);
        game.set_cell(2,3);
        game.set_cell(3,2);
        game.set_cell(3,3);
        Assert::That(game.cell_should_die(3,2), IsFalse());
        Assert::That(game.cell_should_create(3,2), IsFalse());
    }

    It(Should_not_kill_cell_when_not_set)
    {
        GameOfLife game(5,5);
        for (int y = 1; y <= 3; y++)
        {
            for (int x = 1; x <= 3; x++)
            {
                game.set_cell(x,y);
            }
        }
        game.clear_cell(2,2);
        Assert::That(game.cell_should_die(2,2), IsFalse());
        Assert::That(game.cell_should_create(2,2), IsFalse());
    }

    It(Should_update_game_state)
    {
        GameOfLife game;
        istringstream input(simple_game);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(empty_game));
    }

    It(Should_update_game_state_simple)
    {
        GameOfLife game;
        istringstream input(simple_game_two);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(simple_game_three));
    }

    It(Should_update_game_state_no_change)
    {
        GameOfLife game;
        istringstream input(simple_game_three);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(simple_game_three));
    }

    It(Should_update_game_state_min_edge)
    {
        GameOfLife game;
        istringstream input(simple_game_four);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(simple_game_five));
    }

    It(Should_update_game_state_max_edge)
    {
        GameOfLife game;
        istringstream input(simple_game_six);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(simple_game_seven));
    }

    It(Should_not_change_beehive)
    {
        GameOfLife game;
        istringstream input(beehive);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(beehive));
    }

    It(Should_not_change_loaf)
    {
        GameOfLife game;
        istringstream input(loaf);
        ostringstream output;

        input >> game;
        game.step();
        output << game;

        Assert::That(output.str(), Equals(loaf));
    }

};

int main(int argc, char* argv[]) {

    return igloo::TestRunner::RunAllTests(argc, argv);
}
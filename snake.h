#include <deque>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

#include "view.h"

class Snake
{
    private:
        // cant play a game you cant see
        View view;

        // quadratic grid size
        const int grid_size = 20;

        // grid symbols
        enum symbol {
            empty = 32, snake = 219, food = 177
        };

        // saves state of the grid
        unsigned char grid[20][20] = {char(symbol::empty)};

        // saves the state of the snake with all occupied points
        // starts with size of 3 in the middle of the grid
        std::deque<std::pair<int, int>> snake_body = {
            std::make_pair(grid_size/2, 5),
            std::make_pair(grid_size/2, 4),
            std::make_pair(grid_size/2, 3)
        };

        // current movement direction
        char curr_dir = 'r';

        // direction map
        std::unordered_map<char, std::pair<int, int>> dir_map = {
            {'l', std::make_pair(0, -1)},
            {'r', std::make_pair(0, 1)},
            {'u', std::make_pair(-1, 0)},
            {'d', std::make_pair(1, 0)}
        };

        // player input map
        std::unordered_map<char, char> input_map = {
            {'w', 'u'},
            {'a', 'l'},
            {'s', 'd'},
            {'d', 'r'}
        };

        // speed
        int speed = 15;

        // deadeg
        bool dead = false;

        // food
        std::pair<int, int> food_pos;

        // rows to update
        int rows = 0;

        // functions

        void update_view();

        int add_row_to_update(int row);

        void reset_rows_to_update();

        // spawn food at empty and random location
        void spawn_food_random();

        // get all free spaces to spawn food in
        std::vector<std::pair<int, int>> get_free_spaces();

        // update direction using last input
        void update_direction();

        // update position()
        void move();

        // return true if play input is opposite direction
        bool opposite_direction(char c);

        // modulo so that negative numbers dont mess up my code
        int mod(int a, int b);

        // sleep
        void sleep(int ms);

        // calculate score
        int score();
    public:
        Snake();
        void run();
};
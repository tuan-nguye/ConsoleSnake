#include <deque>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

class Snake
{
    private:
        // quadratic grid size
        const int grid_size = 20;

        // saves state of the grid
        int grid[20][20] = {0};

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
        std::pair<int, int> food;

        // ascii art txt
        std::string start_img_path = "ascii-art-snek.txt";

        // functions

        // what would a game without a proper start screen be
        void show_start_screen();

        // show board
        void show();

        // show score for extra motivation
        void show_score();

        // spawn food at empty and random location
        void spawn_food_random();

        std::vector<std::pair<int, int>> get_free_spaces();

        // update direction using last input
        void update_direction();

        // update position()
        void move();

        bool opposite_direction(char c);

        // modulo so that negative numbers dont mess up my code
        int mod(int a, int b);

        // reset cursor
        void reset_cursor();

        // sleep
        void sleep();
    public:
        Snake();
        void run();
};
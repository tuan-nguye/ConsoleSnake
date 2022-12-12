#include <deque>
#include <unordered_map>
#include <utility>
#include <vector>

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
            {'u', std::make_pair(1, 0)},
            {'d', std::make_pair(-1, 0)}
        };

        // speed
        int speed = 3;

        // food
        std::pair<int, int> food = std::make_pair(10, 10);

        // functions

        // show board
        void show();

        // spawn food at empty and random location
        void spawn_food_random();

        std::vector<std::pair<int, int>> get_free_spaces();

        // get last keyboard input
        void get_input();

        // update direction using last input
        void update_direction();

        // update position()
        void move();

        // reset cursor
        void reset_cursor();
    public:
        Snake();
        void run();
};
#include <string>
#include <utility>

class View
{
    private:
        // ascii art txt
        std::string start_img_path = "ascii-art-snek.txt";

        // console cursor offset
        std::pair<int, int> cursor_offset;

        // offset for score
        std::pair<int, int> score_offset;

        int grid_size = 20;

        // reset cursor
        void set_cursor_pos(int x, int y);

        std::pair<int, int> get_cursor_pos();

        // every good game needs a proper start screen
        void show_start_screen();

        // game over
        void show_end_screen();

        // show board
        void show_grid(int grid[20][20]);
        
        void set_cursor_visibility(bool visible);

    public:
        View();
        
        enum chars {
            corner_up_left = 201, corner_up_right = 187, corner_down_left = 200, corner_down_right = 188,
            horizontal_bar = 205, vertical_bar = 186, empty = 32,
            snake = 219, food = 177
        };

        void start(int grid[20][20]);
        void end();        

        // update single cells
        void update_cell(int x, int y, int char_code);
        
        // show score for extra motivation
        void show_score(int score);
};
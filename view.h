#include <string>
#include <utility>
#include <vector>

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

        int logo_width = 80;
        int logo_height = 13;

        void set_cursor_pos(int x, int y);

        // set cursor + offset
        void set_cursor_by_offset(int x, int y);

        // adapted to windows coords
        void set_cursor_adapted(int x, int y);

        std::pair<int, int> get_cursor_pos();

        // every good game needs a proper start screen
        void show_start_screen();

        // show board
        void show_grid(int grid[20][20]);

        void animate_logo();

        void hide_start_screen();

        // game over
        void show_end_screen();
        
        void set_cursor_visibility(bool visible);

        void sleep(int ms);

    public:
        View();
        
        enum chars {
            corner_up_left = 201, corner_up_right = 187, corner_down_left = 200, corner_down_right = 188,
            horizontal_bar = 205, vertical_bar = 186, empty = 32,
            snake = 219, food = 177
        };

        void start(int grid[20][20]);

        void end();        

        void update_row(int row[20], int rowIdx);
        
        // show score for extra motivation
        void show_score(int score);
};
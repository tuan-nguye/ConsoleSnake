#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <fstream>
#include <windows.h>

#include "snake.h"

void Snake::run()
{
    set_cursor_visibility(false);
    show_start_screen();

    while(!dead) {
        // update direction, from user input or keep if no key was pressed
        update_direction();
        // move snake by one cell and react to cases: food, snake, empty cell
        move();
        // update the view on the console
        update_view();
        // sleep depending on the speed variable
        sleep();
    }

    std::cout << "R I P B O Z O" << '\n';
    set_cursor_visibility(true);
}

Snake::Snake()
{
    spawn_food_random();

    for(auto& pos : snake_body)
    {
        grid[pos.first][pos.second] = 1;
    }

    grid[food.first][food.second] = 2;

    cursor_offset = get_cursor_pos();
}

void Snake::show_start_screen()
{
    // TODO cool animation instead of just printing
    std::ifstream img_txt(start_img_path);
    std::string line;
    int width = 0;

    if(img_txt.is_open())
    {
        while(std::getline(img_txt, line))
        {
            std::cout << line << '\n';
            width = line.length();
        }
        std::cout.flush();
    }

    img_txt.close();

    std::cout << "Press any key to continue" << std::endl;
    std::cout << "Controls: wasd" << std::endl;

    // clear starting screen
    getch();
    set_cursor_pos(cursor_offset.first, cursor_offset.second);
    std::string clear_line(width, ' ');
    std::string clear;

    for(int i = 0; i < grid_size; i++)
    {
        clear += clear_line + '\n';
    }

    std::cout << clear << std::endl;
}

void Snake::update_view()
{
    set_cursor_pos(cursor_offset.first, cursor_offset.second);
    show_grid();
    show_score();
}

void Snake::show_grid()
{
    std::string out((grid_size+1)*2, '_');
    out += '\n';

    for(int i = 0; i < grid_size; i++)
    {
        out += '|';

        for(int j = 0; j < grid_size; j++)
        {
            if(grid[i][j] == 0) out += "  ";
            else if(grid[i][j] == 1) out += "[]";
            else if(grid[i][j] == 2) out += "@@";
        }

        out += "|\n";
    }

    out.append((grid_size+1)*2, '-');
    std::cout << out << std::endl;
}

void Snake::show_score()
{
    std::cout << "Score: " << (snake_body.size()-3) * 10 << std::endl;
}

void Snake::move()
{
    std::pair<int, int> head = snake_body.front();
    std::pair<int, int> dir = dir_map[curr_dir];
    int x = mod(head.first+dir.first, grid_size), y = mod(head.second+dir.second, grid_size);
    std::pair<int, int> curr(x, y);

    // Deadge, ripbozo
    if(grid[x][y] == 1)
    {
        dead = true;
        return;
    }

    snake_body.push_front(curr);
    grid[x][y] = 1;

    if(x == food.first && y == food.second)
    {
        spawn_food_random();
    } else
    {
        std::pair<int, int> last = snake_body.back();
        snake_body.pop_back();
        grid[last.first][last.second] = 0;
    }
}

int Snake::mod(int a, int b)
{
    return (a%b + b) % b;
}

void Snake::spawn_food_random()
{
    std::vector<std::pair<int, int>> free_spaces = get_free_spaces();
    int random_idx = rand() % free_spaces.size();
    food = free_spaces.at(random_idx);
    grid[food.first][food.second] = 2;
}

std::vector<std::pair<int, int>> Snake::get_free_spaces()
{
    std::vector<std::pair<int, int>> free_spaces;

    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            if(grid[i][j] == 0) {
                free_spaces.push_back(std::make_pair(i, j));
            }
        }
    }

    return free_spaces;
}

void Snake::update_direction()
{
    if(!kbhit()) return;
    char input = std::tolower(getch());
    if(input_map.count(input) == 0) return;
    if(opposite_direction(input_map[input])) return;
    curr_dir = input_map[input];
}

bool Snake::opposite_direction(char c)
{
    if(c == 'l') return curr_dir == 'r';
    else if(c == 'r') return curr_dir == 'l';
    else if(c == 'u') return curr_dir == 'd';
    else if(c == 'd') return curr_dir == 'u';

    return false;
}

void Snake::set_cursor_pos(int x, int y)
{
    COORD cursor_pos;
    cursor_pos.X = x;
    cursor_pos.Y = y;
    if(!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos))
    {
        exit(-2);
    }

}

std::pair<int, int> Snake::get_cursor_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi = {};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD coord = csbi.dwCursorPosition;
    return std::make_pair(coord.X, coord.Y);
}

void Snake::set_cursor_visibility(bool visible)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(out, &cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(out, &cci);
}

void Snake::sleep()
{
    std::chrono::milliseconds timespan(1000/speed);
    std::this_thread::sleep_for(timespan);
}
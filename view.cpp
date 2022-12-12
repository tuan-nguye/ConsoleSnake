#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <fstream>
#include <windows.h>

#include "view.h"

View::View()
{
    cursor_offset = get_cursor_pos();
    score_offset = std::make_pair(cursor_offset.first, cursor_offset.second+grid_size+2);
    cursor_offset.first++;
    cursor_offset.second++;
}

void View::start(int grid[20][20])
{
    set_cursor_visibility(false);
    show_start_screen();
    show_grid(grid);
}

void View::end()
{
    show_end_screen();
    set_cursor_visibility(true);
}

void View::show_start_screen()
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
    std::string clear_line(width, chars::empty);
    std::string clear;

    for(int i = 0; i < grid_size; i++)
    {
        clear += clear_line + '\n';
    }

    std::cout << clear << std::endl;
}

void View::show_end_screen()
{
    set_cursor_pos(score_offset.first, score_offset.second+1);
    std::cout << "R I P B O Z O" << '\n';
    std::cout << "Press any to exit" << std::endl;
    getch();
}

void View::show_grid(int grid[20][20])
{
    set_cursor_pos(cursor_offset.first-1, cursor_offset.second-1);

    std::string out;
    out += char(chars::corner_up_left);
    out.append(grid_size*2, char(chars::horizontal_bar));
    out += char(chars::corner_up_right);
    out += '\n';

    for(int i = 0; i < grid_size; i++)
    {
        out += char(chars::vertical_bar);

        for(int j = 0; j < grid_size; j++)
        {
            if(grid[i][j] == 0) out += "  ";
            else if(grid[i][j] == 1) out.append(2, char(chars::snake));
            else if(grid[i][j] == 2) out.append(2, char(chars::food));
        }

        out += char(chars::vertical_bar);
        out += '\n';
    }

    out += char(chars::corner_down_left);
    out.append(grid_size*2, char(chars::horizontal_bar));
    out += char(chars::corner_down_right);
    std::cout << out << std::endl;
}

void View::update_cell(int x, int y, int char_code)
{
    if(x < 0 || x >= grid_size || y < 0 || y >= grid_size) return;

    char c = char(char_code);
    set_cursor_pos(cursor_offset.first+y*2, cursor_offset.second+x);
    std::cout << c << c;
    std::cout.flush();
}

void View::show_score(int score)
{
    set_cursor_pos(score_offset.first, score_offset.second);
    std::cout << "Score: " << score << std::endl;
}

void View::set_cursor_pos(int x, int y)
{
    COORD cursor_pos;
    cursor_pos.X = x;
    cursor_pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
}

std::pair<int, int> View::get_cursor_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi = {};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD coord = csbi.dwCursorPosition;
    return std::make_pair(coord.X, coord.Y);
}

void View::set_cursor_visibility(bool visible)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(out, &cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(out, &cci);
}
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <chrono>
#include <thread>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>

#include "view.h"

View::View()
{
    cursor_offset = get_cursor_pos();
    score_offset = std::make_pair(cursor_offset.first, cursor_offset.second+grid_size+2);
    cursor_offset.first++;
    cursor_offset.second++;
}

void View::start(char grid[20][20])
{
    set_cursor_visibility(false);
    show_start_screen();
    show_grid(grid);
}

// TODO start screen animation
void View::show_start_screen()
{
    set_cursor_adapted(grid_size, 0);
    animate_logo();

    set_cursor_adapted(logo_height, 0);
    std::cout << "Press any key to continue" << std::endl;
    std::cout << "Controls: wasd" << std::endl;
    getch();

    hide_start_screen();
}

void View::animate_logo()
{
    // TODO cool animation instead of just printing
    std::ifstream img_txt(start_img_path);
    std::string line;
    int i = 0;
    std::vector<std::tuple<int, int, char>> to_show;

    if(img_txt.is_open())
    {
        while(std::getline(img_txt, line))
        {
            for(int j = 0; j < line.length(); j++)
            {
                char c = line[j];
                if(c != ' ') to_show.push_back(std::make_tuple(i, j, c));
            }

            i++;
        }
    }

    img_txt.close();
    bool skip = false;

    while(!to_show.empty())
    {
        for(int i = 0; i < 2; i++)
        {
            int rand_idx = rand() % to_show.size();
            std::tuple<int, int, char> pos = to_show.at(rand_idx);
            to_show.erase(to_show.begin()+rand_idx);

            set_cursor_adapted(std::get<0>(pos), std::get<1>(pos));
            std::cout << std::get<2>(pos);
            std::cout.flush();

            if(kbhit()) {
                skip = true;
                getch();
            }
        }
        
        if(!skip) sleep(1);
    }
}

void View::hide_start_screen()
{
    set_cursor_pos(cursor_offset.first, cursor_offset.second);
    std::string clear_line(logo_width, border::empty);
    std::string clear;

    for(int i = 0; i < grid_size; i++)
    {
        clear += clear_line + '\n';
    }

    std::cout << clear << std::endl;
}

void View::end()
{
    show_end_screen();
    set_cursor_visibility(true);
}

void View::show_end_screen()
{
    set_cursor_pos(score_offset.first, score_offset.second+1);
    std::cout << "R I P B O Z O" << '\n';
    std::cout << "Press any to exit" << std::endl;
    getch();
}

void View::show_grid(char grid[20][20])
{
    set_cursor_by_offset(-1, -1);

    std::string out;
    out += char(border::corner_up_left);
    out.append(grid_size*2, char(border::horizontal_bar));
    out += char(border::corner_up_right);
    out += '\n';

    for(int i = 0; i < grid_size; i++)
    {
        out += char(border::vertical_bar);

        for(int j = 0; j < grid_size; j++)
        {
            out.append(2, grid[i][j]);
        }

        out += char(border::vertical_bar);
        out += '\n';
    }

    out += char(border::corner_down_left);
    out.append(grid_size*2, char(border::horizontal_bar));
    out += char(border::corner_down_right);
    std::cout << out << std::endl;
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

void View::set_cursor_by_offset(int x, int y)
{
    set_cursor_pos(cursor_offset.first+x, cursor_offset.second+y);
}

void View::set_cursor_adapted(int x, int y)
{
    set_cursor_by_offset(y, x);
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

void View::update_row(char row[20], int rowIdx)
{
    std::string out;

    for(int i = 0; i < grid_size; i++)
    {
        out.append(2, row[i]);
    }

    set_cursor_adapted(rowIdx, 0);
    std::cout << out;
    std::cout.flush();
}

void View::sleep(int ms)
{
    std::chrono::milliseconds timespan(ms);
    std::this_thread::sleep_for(timespan);
}
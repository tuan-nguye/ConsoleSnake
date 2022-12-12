#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <chrono>
#include <thread>

#include "snake.h"

void Snake::run()
{
    while(true) {
        update_direction();
        move();
        show();
        sleep();
    }
}

Snake::Snake()
{

    for(auto& pos : snake_body)
    {
        grid[pos.first][pos.second] = 1;
    }

    grid[food.first][food.second] = 2;
}

void Snake::show()
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

void Snake::move()
{
    std::pair<int, int> head = snake_body.front();
    std::pair<int, int> dir = dir_map[curr_dir];
    int x = mod(head.first+dir.first, grid_size), y = mod(head.second+dir.second, grid_size);
    std::pair<int, int> curr(x, y);

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

void Snake::sleep()
{
    std::chrono::milliseconds timespan(1000/speed);
    std::this_thread::sleep_for(timespan);
}
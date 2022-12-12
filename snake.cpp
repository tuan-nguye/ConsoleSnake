#include <iostream>
#include <stdlib.h>

#include "snake.h"

void Snake::run()
{
    for(int i = 0; i < 10; i++) {
        show();
        move();
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
    int x = head.first+dir.first, y = head.second+dir.second;
    std::pair<int, int> curr(x, y);

    snake_body.push_front(curr);
    grid[x][y] = 1;

    if(x == food.first && y == food.second)
    {
        food.first = -1;
        food.second = -1;
    } else
    {
        std::pair<int, int> last = snake_body.back();
        snake_body.pop_back();
        grid[last.first][last.second] = 0;
    }
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

void Snake::get_input()
{

}

void Snake::update_direction()
{

}
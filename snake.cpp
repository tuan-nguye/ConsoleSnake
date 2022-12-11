
#include "snake.h"
#include <iostream>

void Snake::run()
{
    for(int i = 0; i < 10; i++) {
        show();
        move();
    }
}

Snake::Snake()
{
    std::unordered_set<std::pair<int, int>> occupied;

    for(auto& pos : snake_body)
    {
        grid[pos.first][pos.second] = 1;
        occupied.insert(pos);
    }

    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            std::pair<int, int> pair(i, j);
            if(!occupied.contains(pair)) {
                free_spaces.insert(pair);
            }
        }
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
    free_spaces.erase(curr);

    if(x == food.first && y == food.second)
    {
        food.first = -1;
        food.second = -1;
    } else
    {
        std::pair<int, int> last = snake_body.back();
        snake_body.pop_back();
        grid[last.first][last.second] = 0;
        free_spaces.insert(last);
    }
}

void Snake::spawn_food_random()
{
    
}

void Snake::get_input()
{

}

void Snake::update_direction()
{

}
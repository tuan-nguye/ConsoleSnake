#include <stdlib.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "snake.h"

void Snake::run()
{
    view.start(grid);
    spawn_food_random();

    while(!dead) {
        // update direction, from user input or keep if no key was pressed
        update_direction();
        // move snake by one cell and react to cases: food, snake, empty cell
        move();
        // update score
        update_view();
        // sleep depending on the speed variable
        sleep(1000/speed);
    }

    view.end();
}

Snake::Snake()
{
    for(auto& pos : snake_body)
    {
        grid[pos.first][pos.second] = symbol::snake;
    }
}

void Snake::move()
{
    std::pair<int, int> head = snake_body.front();
    std::pair<int, int> dir = dir_map[curr_dir];
    int x = mod(head.first+dir.first, grid_size), y = mod(head.second+dir.second, grid_size);
    std::pair<int, int> curr(x, y);

    // Deadge, ripbozo
    if(grid[x][y] == symbol::snake)
    {
        dead = true;
        return;
    }

    snake_body.push_front(curr);
    grid[x][y] = symbol::snake;
    rows = add_row_to_update(x);

    if(x == food_pos.first && y == food_pos.second)
    {
        spawn_food_random();
    } else
    {
        std::pair<int, int> last = snake_body.back();
        snake_body.pop_back();
        grid[last.first][last.second] = symbol::empty;
        rows = add_row_to_update(last.first);
    }
}

int Snake::mod(int a, int b)
{
    return (a%b + b) % b;
}

void Snake::update_view()
{
    for(int i = 0; i < 32; i++) if(rows & (1<<i)) view.update_row(grid[i], i);
    reset_rows_to_update();
    view.show_score(score());
}

int Snake::add_row_to_update(int row)
{
    return rows | (1<<row);
}

void Snake::reset_rows_to_update()
{
    rows = 0;
}

void Snake::spawn_food_random()
{
    std::vector<std::pair<int, int>> free_spaces = get_free_spaces();
    int random_idx = rand() % free_spaces.size();
    food_pos = free_spaces.at(random_idx);
    grid[food_pos.first][food_pos.second] = symbol::food;
    rows = add_row_to_update(food_pos.first);
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

void Snake::sleep(int ms)
{
    std::chrono::milliseconds timespan(ms);
    std::this_thread::sleep_for(timespan);
}

int Snake::score()
{
    return (snake_body.size()-3) * 10;
}
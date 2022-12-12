#include "snake.h"
#include <unordered_set>
#include <utility>
#include <stdint.h>
#include <iostream>

struct pair_hash
{
    inline std::size_t operator()(std::pair<int, int> &v) const
    {
        return v.first+v.second;
    }
};


int main()
{
    Snake snake;
    snake.run();
}
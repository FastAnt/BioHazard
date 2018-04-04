#pragma once

#include <iostream>
#include <array>
#include "Cell.h"

namespace hazard {

class GameField
{
public:

    void change_cell(int x, int y, Owner owner, uint32_t score);

    Cell* get_cell(int x, int y);
    Owner* get_owner_of_cell(int x, int y);
    std::uint32_t get_score(int x, int y);
    char get_task_of_cell(int x, int y);

private:

    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    std::array<std::array<Cell, WIDTH>, HEIGHT> m_field;
};

} // hazard

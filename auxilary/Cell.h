#pragma once

#include "Owner.h"
#include <iostream>
#include <limits>

namespace hazard {

struct Cell
{
    Owner m_owner;
    uint32_t best_score = std::numeric_limits< uint32_t >::max( );
    char task_ID = "";
};

}  // hazard

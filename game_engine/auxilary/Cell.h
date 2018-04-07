#pragma once

#include <iostream>
#include <limits>
#include <QString>

namespace hazard {

struct Cell
{
    QString m_owner;
    uint32_t best_score = std::numeric_limits< uint32_t >::max( );
    QString task_ID = "";
};

}  // hazard

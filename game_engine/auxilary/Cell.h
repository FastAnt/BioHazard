#pragma once

#include <iostream>
#include <QString>

namespace hazard {

struct Cell
{
    QString m_owner;
    uint32_t m_best_score = -1;
    QString m_task_ID;
    int m_x = -1;
    int m_y = -1;
};

}  // hazard

#pragma once

#include <iostream>

namespace hazard {

struct Owner
{
    Owner ()
    {
        m_team_name = "no team";
        m_id = OwnerId::no_team;
    }

    std::string m_team_name;

    enum class OwnerId
    {
        no_team = -1,
        team_red = 0,
        team_green,
        team_blue,
        team_purple
    };

    OwnerId m_id = OwnerId::no_team;
};

}  // hazard

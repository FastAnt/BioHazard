#pragma once

#include <iostream>
#include <array>
#include "Cell.h"
#include "Owner.h"
#include <map>
#include <algorithm>
#include <cstdlib>      // std::rand, std::srand

namespace hazard {

static int myrandom (int i) { return std::rand()%i;}
class GameField
{
public:

    void change_cell(int x, int y, QString owner, uint32_t score);



    Cell * get_cell_for_turn(QString player_name)
    {
        std::map<Cell *,std::pair<int, int>> owner_cells;
        for(int x = 0 ; x < WIDTH; x++)
        {
            for(int y = 0 ; y < HEIGHT; y++)
            {
                if(cellArray[x][y].m_owner == player_name)
                {
                    owner_cells[&(cellArray[x][y])] =std::make_pair(x,y);
                }
            }
        }

        if(owner_cells.empty())
        {
            return nullptr; // player has no any cell
        }
        for (auto & owner_cell : owner_cells)
        {
            enum pos
            {
                left        = 0,
                top_left    = 1,
                top         = 2,
                top_right   ,
                right       ,
                right_bottom,
                bottom      ,
                bottom_left
            };
            std::vector<int> directions =
            {
                left        ,
                top_left    ,
                top         ,
                top_right   ,
                right       ,
                right_bottom,
                bottom      ,
                bottom_left
            };
            // !!! possible to use just vector of neighbors, but purpose that random_shuffle doesnt correct work with pairs,
            // or random sort fust depend on first arg
            std::map<int,std::pair<int, int>> neighbors  {
                {left        ,{owner_cell.second.first-1, owner_cell.second.second   }}, //  left
                {top_left    ,{owner_cell.second.first-1, owner_cell.second.second-1 }}, // top left
                {top         ,{owner_cell.second.first, owner_cell.second.second-1   }}, // top
                {top_right   ,{owner_cell.second.first+1, owner_cell.second.second-1 }}, // top right
                {right       ,{owner_cell.second.first+1, owner_cell.second.second   }}, // right
                {right_bottom,{owner_cell.second.first+1, owner_cell.second.second+1 }}, // right bottom
                {bottom      ,{owner_cell.second.first, owner_cell.second.second+1   }}, // bottom
                {bottom_left ,{owner_cell.second.first -1, owner_cell.second.second+1}} //  bottom left
            };



            std::random_shuffle ( directions.begin(), directions.end() );
            std::random_shuffle ( directions.begin(), directions.end(), myrandom);

            for(auto & direction :directions)
            {
                auto neighbor_cell = get_cell(neighbors[direction].first, neighbors[direction].second);
                if(neighbor_cell)
                {
                    if(neighbor_cell->m_owner != player_name)
                    {
                        return neighbor_cell;
                    }
                }
            }
        }
        return nullptr;
    }

    Cell* get_cell(int x, int y)
    {
        if(x<WIDTH && y < HEIGHT)
        {
            return &cellArray[x][y];
        }else
        {
            return nullptr;
        }

    }
    QString get_owner_of_cell(int x, int y)
    {
        auto cell = get_cell(x,y);
        if(cell)
        {
            return cell->m_owner;
        }
        else
        {
            // TODO provide logic of no owner possible
            return "";
        }
    }
    std::uint32_t get_score(int x, int y)
    {
        auto cell = get_cell(x,y);
        if(cell)
        {
            return cell->best_score;
        }
        else
        {
            return  std::numeric_limits< uint32_t >::max( );
        }
    }
    QString get_task_id(int x, int y)
    {
        auto cell = get_cell(x,y);
        if(cell)
        {
            return cell->task_ID;
        }
        else
        {
            return  "";
        }
    }

    void save();
    void load()
    {
    }
    void init();
private:

    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    //std::array<std::array<Cell, WIDTH>, HEIGHT> m_field;
    Cell cellArray[WIDTH][HEIGHT];
};

} // hazard

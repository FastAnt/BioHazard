#include "GameField.h"
#include <map>
#include <algorithm>
#include <cstdlib>      // std::rand, std::srand
#include <assert.h>
#include <QFile>

namespace hazard {

static const QString DB_name("./game_field.sqlite");

static int myrandom (int i)
{
    return std::rand()%i;
}

GameField::GameField()
    :m_field_DB(QSqlDatabase::addDatabase( "QSQLITE" ))
    ,m_qry(m_field_DB)
{

}

Cell* GameField::get_cell_for_turn(QString player_name)
{
    std::map<Cell*, std::pair<int, int>> owner_cells;
    for(int x = 0 ; x < WIDTH; x++)
    {
        for(int y = 0 ; y < HEIGHT; y++)
        {
            if(cellArray[x][y].m_owner == player_name)
            {
                owner_cells[&(cellArray[x][y])] = std::make_pair(x,y);
            }
        }
    }

    if(owner_cells.empty())
    {
        return nullptr; // player has no cells
    }
    for (auto& owner_cell : owner_cells)
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

        for(auto& direction :directions)
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

Cell* GameField::get_cell(int x, int y)
{
    if( x < WIDTH && y < HEIGHT)
    {
        return &cellArray[x][y];
    }
    else
    {
        return nullptr;
    }
}

QString GameField::get_owner_of_cell(int x, int y)
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

uint32_t GameField::get_score(int x, int y)
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

QString GameField::get_task_id(int x, int y)
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

void GameField::save()
{

}

void GameField::load()
{
    if(!connect_to_db() || !verify_db_size())
    {
        qDebug()<<"Game Field is Empty!";
        return;
    }

    m_qry.prepare("SELECT * FROM single_table");
    if(!m_qry.exec())
    {
        assert("cannot read data from DB!");
    }
    // size is already verified
    for (int current_cell_ind = 0; m_qry.next(); ++current_cell_ind)
    {
        Cell* cur_cell = get_cell(current_cell_ind%WIDTH, current_cell_ind/WIDTH);
        cur_cell->m_owner = QString( m_qry.value(1).toString() );
        cur_cell->best_score = m_qry.value(2).toInt();
        cur_cell->task_ID = QString(m_qry.value(3).toString());
    }
}

void GameField::init()
{

}

bool GameField::connect_to_db()
{
    if(!QFile::exists(DB_name))
    {
        qDebug()<< "no DB found! A new DB is about to be created!";
        //assert("no DB found! A new DB is about to be created!");
    }

    m_field_DB.setDatabaseName(DB_name);
    if( !m_field_DB.open() )
    {
        qDebug() << m_field_DB.lastError();
        qFatal( "Failed to connect." );
        return false;
    }
    qDebug()<<"connected";
    return true;
}

bool GameField::create_dummy_db_table()
{
    if(!connect_to_db())
    {
        qDebug()<<"could not create db";
        return false;
    }
    m_qry.prepare("CREATE TABLE single_table"
                  "("
                  "cellNumber INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                  "owner TEXT DEFAULT 'no_team', "
                  "score INTEGER NOT NULL DEFAULT -1, "
                  "task TEXT NOT NULL DEFAULT '1' "
                  ");");
    if (!m_qry.exec())
    {
        qDebug()<<"FAILED TO CREATE DB";
        return false;
    }

    QString dummy_task("1");        // TODO -- put some thought into default task_ID
    for (int i = 0; i < WIDTH*HEIGHT; ++i)
    {
        m_qry.prepare("insert into single_table (task) values('"+dummy_task+"')");
        if(!m_qry.exec())
        {
            qDebug()<< m_qry.lastError().text();
            return false;
        }
    }
    return true;
}

bool GameField::verify_db_size()
{
    m_qry.clear();
    m_qry.prepare("SELECT COUNT(cellNumber) FROM single_table;");
    if(!m_qry.exec())
    {
        qDebug("cannot count number of elements in table, try creating a new dummy one");
        if (!create_dummy_db_table())
        {
            return false;
        }
    }

    m_qry.first(); // yeah, this must be done
    int DB_quantity = m_qry.value(0).toInt();
    qDebug()<<"db has " << DB_quantity << "cells";
    if (DB_quantity == 0)
    {
        qDebug()<<"creating dummy DB because current one is empty";
        create_dummy_db_table();
    }

    assert(DB_quantity == WIDTH*HEIGHT && "corrupt DB - shall we create a dummy?" );

    return true;
}

} // hazard
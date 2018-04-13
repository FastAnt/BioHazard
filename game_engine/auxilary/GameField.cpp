#include "GameField.h"
#include <map>
#include <algorithm>
#include <cstdlib>      // std::rand, std::srand
#include <assert.h>
#include <QFile>
#include <ctime>

namespace hazard {

static const QString DB_name("./game_field.sqlite");
static const int owner_index_in_db = 1;
static const int score_index_in_db = 2;
static const int task_index_in_db = 3;

static int myrandom (int i)
{
    std::srand(std::time(0));
    return std::rand()%i;
}


GameField::GameField()
    :m_field_DB(QSqlDatabase::addDatabase( "QSQLITE" ))
    ,m_qry(m_field_DB)
{
}

void GameField::change_cell(int x, int y, const QString& owner, double score)
{
    assert (x < WIDTH && y < HEIGHT && "cell out of field");

    Cell* cur_cell = get_cell(x, y);
    cur_cell->m_owner = owner;
    cur_cell->m_best_score = score;
    assert(save_cell_to_db(x, y, owner, score) && "cannot afford not saving cell - fall");
}

void get_valid_cord()
{

}
Cell* GameField::get_cell_for_turn(QString player_name)
{
    std::map<Cell*, std::pair<int, int>> owner_cells;
    std::vector<std::pair<int, int>> owner_cells_;
    for(int x = 0 ; x < WIDTH; x++)
    {
        for(int y = 0 ; y < HEIGHT; y++)
        {
            qDebug() << get_cell(x,y)->m_owner;
            if(get_cell(x,y)->m_owner == player_name)
            {
                owner_cells[&(cellArray[x][y])] = std::make_pair(x,y);
                owner_cells_.push_back(std::make_pair(x,y));
            }
        }
    }

    if(owner_cells.empty())
    {
        return nullptr; // player has no cells
    }

    std::random_shuffle ( owner_cells_.begin(), owner_cells_.end() );
    std::random_shuffle ( owner_cells_.begin(), owner_cells_.end(), myrandom);



    for (auto& owner_cell : owner_cells_)
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
            {left        ,{owner_cell.first-1, owner_cell.second   }}, //  left
            {top_left    ,{owner_cell.first-1, owner_cell.second-1 }}, // top left
            {top         ,{owner_cell.first, owner_cell.second-1   }}, // top
            {top_right   ,{owner_cell.first+1, owner_cell.second-1 }}, // top right
            {right       ,{owner_cell.first+1, owner_cell.second   }}, // right
            {right_bottom,{owner_cell.first+1, owner_cell.second+1 }}, // right bottom
            {bottom      ,{owner_cell.first, owner_cell.second+1   }}, // bottom
            {bottom_left ,{owner_cell.first -1, owner_cell.second+1}} //  bottom left
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
        if( x >=0 && y >= 0)
        {
            return &cellArray[x][y];
        }else
        {
            return nullptr;
        }

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

double GameField::get_score(int x, int y)
{
    auto cell = get_cell(x,y);
    if(cell)
    {
        return cell->m_best_score;
    }
    else
    {
        return -1;
    }
}

QString GameField::get_task_id(int x, int y)
{
    auto cell = get_cell(x,y);
    if(cell)
    {
        return cell->m_task_ID;
    }
    else
    {
        return  "";
    }
}

bool GameField::save_cell_to_db(int x, int y, const QString& owner, double score)
{
    int pos_in_db = WIDTH*y + x + 1; // db cellNumber starts from 1
    m_qry.prepare(
                QString("UPDATE single_table SET owner='%1', score=%2"
                        " WHERE cellNumber=%3").arg(owner).arg(score).arg(pos_in_db)
                );
    if(!m_qry.exec())
    {
        qDebug()<<"could not update cell!!!";
        qDebug()<< m_qry.lastError().text();
        return false;
    }
    return true;
}

void GameField::save_all()
{
    for(int x = 0 ; x < WIDTH; x++)
    {
        for(int y = 0 ; y < HEIGHT; y++)
        {
            save_cell_to_db(x, y, get_owner_of_cell(x, y), get_score(x,y));
        }
    }
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
        int x = current_cell_ind % WIDTH;
        int y =  current_cell_ind / WIDTH;
        Cell* cur_cell = get_cell(x,y);
        cur_cell->m_owner = QString( m_qry.value(owner_index_in_db).toString() );
        cur_cell->m_best_score = m_qry.value(score_index_in_db).toDouble();
        cur_cell->m_task_ID = QString(m_qry.value(task_index_in_db).toString());
        cur_cell->m_x = x;
        cur_cell->m_y = y;
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
                  "score REAL NOT NULL DEFAULT -1, "
                  "task TEXT NOT NULL DEFAULT '1' "
                  ");");
    if (!m_qry.exec())
    {
        qDebug()<<"FAILED TO CREATE DB";
        return false;
    }
    std::srand(std::time(nullptr));

    for (int i = 0; i < WIDTH*HEIGHT; ++i)
    {
        int rand_task = 1 + std::rand()/((RAND_MAX + 1u)/20);
        QString dummy_task(QString::number(rand_task));        // TODO -- put some thought into default task_ID
        m_qry.prepare("INSERT INTO single_table (task) VALUES('"+dummy_task+"')");
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
    m_qry.prepare("SELECT COUNT(cellNumber) FROM single_table;");
    if(!m_qry.exec())
    {
        qDebug("cannot count number of elements in table");
        assert(false);
    }

    m_qry.next(); // yeah, this must be done
    int DB_quantity = m_qry.value(0).toInt();
    qDebug()<<"db has " << DB_quantity << "cells";

    assert(DB_quantity == WIDTH*HEIGHT && "corrupt DB - shall we create a dummy?" );

    return true;
}

} // hazard

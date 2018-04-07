#pragma once

#include <iostream>
#include "Cell.h"
#include <QtSql>

namespace hazard {

class GameField
{
public:

    void change_cell(int x, int y, QString owner, uint32_t score);

    GameField();

    Cell* get_cell_for_turn(QString player_name);
    Cell* get_cell(int x, int y);

    QString get_owner_of_cell(int x, int y);
    std::uint32_t get_score(int x, int y);
    QString get_task_id(int x, int y);

    void save();
    void load();
    void init();

private:
    bool connect_to_db();
    bool create_dummy_db_table();
    bool verify_db_size();

private:

    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    //std::array<std::array<Cell, WIDTH>, HEIGHT> m_field;
    Cell cellArray[WIDTH][HEIGHT];

    QSqlDatabase m_field_DB;
    QSqlQuery m_qry;
};

} // hazard

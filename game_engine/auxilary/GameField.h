#pragma once

#include "Cell.h"
#include <QtSql>

namespace hazard {

class GameField
{
public:

    void change_cell(int x, int y, const QString& owner, double score);

    GameField();

    Cell* get_cell_for_turn(QString player_name);
    Cell* get_cell(int x, int y);

    QString get_owner_of_cell(int x, int y);
    double get_score(int x, int y);
    QString get_task_id(int x, int y);

    bool save_cell_to_db(int x, int y, const QString& owner, double score);

    /**
     * @brief save_all is optional - it's better to save only the cells that were changed
     */
    void save_all();

    /**
     * @brief loads GameField from sqlite db
     */
    void load();

    ///? load is used for init purpose
    void init();

    /**
     * @brief needs tasks initial distribution
     * @return success or creating new table
     */
    bool create_dummy_db_table();

private:
    bool connect_to_db();
    bool verify_db_size();

private:

    static const int WIDTH = 30;
    static const int HEIGHT = 30;
    Cell cellArray[WIDTH][HEIGHT];

    QSqlDatabase m_field_DB;
    QSqlQuery m_qry;
};

} // hazard

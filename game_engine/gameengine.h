#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <qvector.h>
#include <QLibrary>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QQuickItemGrabResult>

#include "auxilary/GameField.h"

class GameEngine : public QQuickItem
{
    Q_OBJECT
public:
    explicit GameEngine(QQuickItem *parent = nullptr);
    int getCurrentCell(QString);
    std::pair<QString,QString> getTaskInfo(QString id);

    Q_INVOKABLE void initGame(QString argv);
    Q_INVOKABLE void doTurn();
    Q_INVOKABLE QString get_cell_color(int idx);
    Q_INVOKABLE QString get_cell_task_id(int idx);



signals:

public slots:
    void dump_result();
private :
    std::pair<int , int > get_coordinate_from_id(int id);
    QVector<QString> m_players = {"team1","team2","team3","team4"};
    QMap<QString, QString> m_colors = {{"team1","red"},{"team2","violet "},{"team3","green"},{"team4","yellow"}};
    hazard::GameField m_field;
    QSharedPointer<QQuickItemGrabResult> m_result;
};

#endif // GAMEENGINE_H

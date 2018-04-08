#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <qvector.h>
#include <QLibrary>
#include <QJsonObject>
#include <QJsonDocument>

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

signals:

public slots:
private :
    QVector<QString> m_players = {"player_test","team2","team3","team4"};
    hazard::GameField m_field;
};

#endif // GAMEENGINE_H

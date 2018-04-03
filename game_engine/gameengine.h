#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <qvector.h>
#include <QLibrary>
#include <QJsonObject>
#include <QJsonDocument>

class GameEngine : public QQuickItem
{
    Q_OBJECT
public:
    explicit GameEngine(QQuickItem *parent = nullptr);
    int getCurrentCell(QString);
    QString getTaskInfo(int cellNum);

    Q_INVOKABLE void initGame();
    Q_INVOKABLE void doTurn();

signals:

public slots:
private :
    QVector<QString> m_players = {"player_test","team2","team3","team4"};
};

#endif // GAMEENGINE_H

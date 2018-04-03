#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <qvector.h>
#include <QLibrary>

class Player
{
public:
    Player() = default;
    ~Player() = default;
    int m_id;

    void process()
    {
        qDebug() << "player "<< m_id << " turn";
    }

};

class GameEngine : public QQuickItem
{
    Q_OBJECT
public:
    explicit GameEngine(QQuickItem *parent = nullptr);

    Q_INVOKABLE void initGame();
    Q_INVOKABLE void doTurn();

signals:

public slots:
private :
        QVector<Player> m_players;
};

#endif // GAMEENGINE_H

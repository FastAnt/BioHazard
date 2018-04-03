#include "gameengine.h"

GameEngine::GameEngine(QQuickItem *parent) : QQuickItem(parent)
{

}

int GameEngine::getCurrentCell(QString)
{
    return 1;
}

QString GameEngine::getTaskInfo(int cellNum)
{
    QString val;
    QFile file;
    file.setFileName("test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qDebug() << val;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString::number(cellNum));
    qDebug() << value;
    QJsonObject item = value.toObject();
    qDebug() << tr("QJsonObject of description: ") << item;

    /* in case of string value get value and convert into string*/
    qDebug() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue subobj = item["arg"];
    qDebug() << subobj.toString();
    return subobj.toString();
}

void GameEngine::initGame()
{
    // load player names
}
class Player_test;
void GameEngine::doTurn()
{
    for(auto playerName : m_players)
    {
        QLibrary myLib("./"+playerName);
        myLib.load();
        typedef int (*processMethod)(int);
        if(myLib.isLoaded())
        {
            processMethod run = (processMethod) myLib.resolve("process");
            if (run)
            {
                getTaskInfo(getCurrentCell(playerName));
                run(4);
            }
            else
            {
                qDebug() << "symb not found";
            }
        }
        else
        {
            qDebug() << "not loaded";
        }
    }
}

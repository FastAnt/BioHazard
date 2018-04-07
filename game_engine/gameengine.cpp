#include "gameengine.h"
#include "auxilary/Cell.h"

GameEngine::GameEngine(QQuickItem *parent) : QQuickItem(parent)
{

}

int GameEngine::getCurrentCell(QString)
{
    return 1;
}

std::pair<QString, QString> GameEngine::getTaskInfo( QString id )
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
    QJsonValue value = sett2.value(id);
    qDebug() << value;
    QJsonObject item = value.toObject();
    qDebug() << tr("QJsonObject of description: ") << item;

    /* in case of string value get value and convert into string*/
    qDebug() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue subobj = item["arg"];
    QString arg = subobj.toString();
    subobj = item["res"];
    QString res = subobj.toString();

    return std::make_pair(arg,res);
}

void GameEngine::initGame()
{
    // load player names
    m_field.load();
}

void GameEngine::doTurn()
{
    for(auto playerName : m_players)
    {
        QLibrary myLib("./"+playerName);
        myLib.load();
        typedef int (*processMethod)(std::string,std::string);
        if(myLib.isLoaded())
        {
            processMethod run = (processMethod) myLib.resolve("process");
            if (run)
            {
                hazard::Cell * p_cell_for_turn = m_field.get_cell_for_turn(playerName);
                if(p_cell_for_turn)
                {
                    std::pair<QString,QString> task_arg = getTaskInfo(p_cell_for_turn->task_ID);
                    auto res = run(p_cell_for_turn->task_ID.toStdString(),task_arg.first.toStdString());
                    if(task_arg.second == res)
                    {
                        //player win;
                    }
                }

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

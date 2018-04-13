#include "gameengine.h"
#include "auxilary/Cell.h"
#include <time.h>
#include <math.h>       /* pow */
#include <chrono>

#include "../shared/biohazard_adaptor.h"
#include "../shared/biohazard_interface.h"

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

void GameEngine::initGame( QString argv )
{
//        if (argv == "create")
//        {
//            m_field.create_dummy_db_table();
//        }
//    // load player names
    m_field.load();
}

void GameEngine::doTurn()
{
    for(auto playerName : m_players)
    {
        QLibrary myLib("./"+playerName+"/"+playerName);
        myLib.load();
        typedef std::string (*processMethod)(std::string,std::string);
        if(myLib.isLoaded())
        {try
            {
                processMethod run = (processMethod) myLib.resolve("process");
                if (run)
                {
                    hazard::Cell * p_cell_for_turn = m_field.get_cell_for_turn(playerName);
                    if(p_cell_for_turn)
                    {
                        std::pair<QString,QString> task_arg = getTaskInfo(p_cell_for_turn->m_task_ID);

                        //auto start = clock();
                        std::string res;
                        auto start = std::chrono::system_clock::now();
                        for(int i = 0; i < 100; i++)
                        {
                            res = run(p_cell_for_turn->m_task_ID.toStdString(),task_arg.first.toStdString());
                        }
                        auto end = std::chrono::system_clock::now();
                        std::chrono::duration<double,std::micro> new_time_score = end-start;
                        if(task_arg.second == QString(res.c_str()))
                        {
                            int x = p_cell_for_turn->m_x;
                            int y = p_cell_for_turn->m_y;
                            double old_time_score = m_field.get_score(x, y);
                            if (old_time_score == -1 || new_time_score.count() < old_time_score)
                            {
                                m_field.change_cell(x, y, playerName, new_time_score.count() );
                            }
                        }
                    }
                }
                else
                {
                    qDebug() << "symb not found";
                }
            }
            catch(...)
            {
                qDebug() << "run fail";
            }

        }
        else
        {
            qDebug() << "not loaded";
        }
    }
    m_result = parent()->findChild<QQuickItem*>("game_field")->grabToImage();
    connect(m_result.data(), &QQuickItemGrabResult::ready, this,
            &GameEngine::dump_result);
}

QString GameEngine::get_cell_color(int idx)
{
    if(idx<0)
        return "white";
    auto cord = get_coordinate_from_id(idx);
    auto owner = m_field.get_owner_of_cell(cord.first,cord.second);
    if(m_colors.find(owner)!=m_colors.end())
    {
        return m_colors[owner];
    }
    else
    {
        return "blue";
    }

}

QString GameEngine::get_cell_task_id(int idx)
{
    if(idx<0)
        return "1";
    auto cord = get_coordinate_from_id(idx);
    auto task_id = m_field.get_task_id(cord.first,cord.second);
    return task_id;
}

void GameEngine::dump_result()
{
    QImage dumped(m_result->image());
    dumped.save("./field.png");

    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    dumped.save(&buffer, "PNG");
    buffer.close();

    QString message = array.toBase64();

    new MessageAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/", this);
    new org::biohazard::message(QString(), QString(), QDBusConnection::sessionBus(), this);

    QDBusMessage msg = QDBusMessage::createSignal("/", "org.biohazard.message", "message");
    msg << message;
    QDBusConnection::sessionBus().send(msg);

    qApp->exit();
}

std::pair<int, int> GameEngine::get_coordinate_from_id(int id)
{
    if(id<0)
    {
        return std::make_pair(-1,-1);
    }

    int x = 0 ;
    int y = 0 ;
    x = id%30;
    y = id/30;
    return std::make_pair(x,y);
}

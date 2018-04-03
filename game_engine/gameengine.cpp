#include "gameengine.h"

GameEngine::GameEngine(QQuickItem *parent) : QQuickItem(parent)
{

}

void GameEngine::initGame()
{
    m_players.push_back(Player());
}
class Player_test;
void GameEngine::doTurn()
{
    QLibrary myLib("/home/aamelnytskyi/bioHazard/BioHazard/build-game_engine-Desktop_Qt_5_10_0_GCC_64bit-Debug/libplayer_test.so");
    myLib.load();
    typedef int (*MyPrototype)(int);
    if(myLib.isLoaded())
    {
        MyPrototype myFunction = (MyPrototype) myLib.resolve("Player_test::process");
        if (myFunction)
        {
            myFunction(3);
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

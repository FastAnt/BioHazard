#include "gameengineserver.h"
#include "../shared/biohazard_adaptor.h"
#include "../shared/biohazard_interface.h"

GameEngineServer::GameEngineServer(QObject *parent) : QObject(parent)
{
    new MessageAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/", this);
    new org::biohazard::message(QString(), QString(), QDBusConnection::sessionBus(), this);
    QDBusConnection::sessionBus().connect(QString(), QString(), "org.biohazard.message", "message", this, SLOT(getMessage(QString)));
}

GameEngineServer::~GameEngineServer()
{

}

QString GameEngineServer::message() const
{
    return m_message;
}

void GameEngineServer::getMessage(const QString& base64)
{
    m_message = "data:image/png;base64," + base64;
    qDebug() << "Message:" << base64 << "\n\n";
    emit messageChanged();
}

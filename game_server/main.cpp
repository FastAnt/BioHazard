#include "../shared/websocketclientwrapper.h"
#include "../shared/websockettransport.h"

#include "gameengineserver.h"

#include <QCoreApplication>
#include <QtWebSockets>
#include <QWebChannel>
#include <QtDBus>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Server"), QWebSocketServer::NonSecureMode);

    if(!server.listen(QHostAddress::Any, 3227))
    {
        qFatal("Failed to open web socket server.\n");
        return 1;
    }

    if (!QDBusConnection::sessionBus().isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.\nPlease check your system settings and try again.\n");
        return 1;
    }

    WebSocketClientWrapper clientWrapper(&server);

    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    GameEngineServer* gameServer = new GameEngineServer(&a);
    channel.registerObject(QStringLiteral("gameServer"), gameServer);

    return a.exec();
}

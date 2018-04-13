#ifndef GAMEENGINESERVER_H
#define GAMEENGINESERVER_H

#include <QtCore>
#include <QtGui>

class GameEngineServer : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString message READ message NOTIFY messageChanged )

public:
    explicit GameEngineServer(QObject *parent = nullptr);
    virtual ~GameEngineServer();

    QString message() const;

public slots:
    void getMessage(const QString& base64);

signals:
    void messageChanged();

private:
    QString m_message = "Message";
};

#endif // GAMEENGINESERVER_H

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <memory>
#include "clienthandler.h"
#include "../auth/AuthManager.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(std::shared_ptr<AuthManager> authManager, QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    std::shared_ptr<AuthManager> authManager;
    void handleRequest(ClientHandler *client, const QJsonObject &request);
};

#endif // TCPSERVER_H

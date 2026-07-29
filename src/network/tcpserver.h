#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <memory>
#include "clienthandler.h"
#include "../auth/AuthManager.h"
#include "../managers/bookmanager.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(std::shared_ptr<AuthManager> authManager,BookManager* bookManager, QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    std::shared_ptr<AuthManager> authManager;
    void handleRequest(ClientHandler *client, const QJsonObject &request);
    BookManager* bookManager;
        QJsonObject bookToJson(const Book& book);
};

#endif // TCPSERVER_H

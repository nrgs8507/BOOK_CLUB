#include "tcpserver.h"
#include <QJsonObject>
#include <QDebug>

TcpServer::TcpServer(std::shared_ptr<AuthManager> authManager, QObject *parent)
    : QTcpServer(parent), authManager(authManager) {}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    ClientHandler *client = new ClientHandler(socket, this);

    connect(client, &ClientHandler::requestReceived, this, [this, client](const QJsonObject &request) {
        handleRequest(client, request);
    });
    connect(client, &ClientHandler::disconnected, this, [socket, client]() {
        client->deleteLater();
        socket->deleteLater();
    });

    qDebug() << "Client connected, descriptor:" << socketDescriptor;
}

void TcpServer::handleRequest(ClientHandler *client, const QJsonObject &request)
{
    QString action = request.value("action").toString();
    QJsonObject response;
    response["action"] = action;

    if (action == "login") {
        QString username = request.value("username").toString();
        QString password = request.value("password").toString();
        auto user = authManager->login(username, password);
        if (user) {
            response["status"] = "ok";
            response["username"] = user->getUsername();
            response["fullName"] = user->getFullName();
        } else {
            response["status"] = "error";
            response["message"] = "Invalid username or password.";
        }
    }
    else if (action == "register") {
        QString username = request.value("username").toString();
        bool alreadyExists = authManager->usernameExists(username);
        bool ok = authManager->registerUser(
            username,
            request.value("password").toString(),
            request.value("fullName").toString(),
            request.value("securityQuestion").toString(),
            request.value("securityAnswer").toString()
            );
        response["status"] = ok ? "ok" : "error";
        if (!ok) {
            response["message"] = alreadyExists ? "Username already exists." : "Registration failed.";
        }
    }
    else if (action == "forgotPassword") {
        bool ok = authManager->forgotPassword(
            request.value("username").toString(),
            request.value("securityAnswer").toString(),
            request.value("newPassword").toString()
            );
        response["status"] = ok ? "ok" : "error";
        if (!ok) response["message"] = "Username or security answer is incorrect.";
    }
    else {
        response["status"] = "error";
        response["message"] = "Unknown action: " + action;
    }

    client->sendResponse(response);
}

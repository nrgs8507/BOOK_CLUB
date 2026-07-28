#include "networkclient.h"
#include <QJsonDocument>

NetworkClient::NetworkClient(QObject *parent) : QObject(parent)
{
    connect(&socket, &QTcpSocket::connected, this, &NetworkClient::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &NetworkClient::disconnectedFromServer);
    connect(&socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(&socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        emit connectionError(socket.errorString());
    });
}

void NetworkClient::connectToServer(const QString &host, quint16 port)
{
    socket.connectToHost(host, port);
}

bool NetworkClient::isConnected() const
{
    return socket.state() == QAbstractSocket::ConnectedState;
}

void NetworkClient::sendRequest(const QJsonObject &request)
{
    QJsonDocument doc(request);
    socket.write(doc.toJson(QJsonDocument::Compact));
    socket.write("\n");
}

void NetworkClient::onReadyRead()
{
    buffer.append(socket.readAll());
    int newlineIndex;
    while ((newlineIndex = buffer.indexOf('\n')) != -1) {
        QByteArray line = buffer.left(newlineIndex);
        buffer.remove(0, newlineIndex + 1);
        if (line.trimmed().isEmpty()) continue;

        QJsonDocument doc = QJsonDocument::fromJson(line);
        if (doc.isObject()) emit responseReceived(doc.object());
    }
}
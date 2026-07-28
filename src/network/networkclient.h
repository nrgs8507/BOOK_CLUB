#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit NetworkClient(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendRequest(const QJsonObject &request);
    bool isConnected() const;

signals:
    void connected();
    void disconnectedFromServer();
    void responseReceived(const QJsonObject &response);
    void connectionError(const QString &message);

private slots:
    void onReadyRead();

private:
    QTcpSocket socket;
    QByteArray buffer;
};

#endif // NETWORKCLIENT_H

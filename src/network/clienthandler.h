#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

// هر شیء از این کلاس نماینده‌ی یک کلاینت متصل به سرور است.
// وظیفه‌اش: خوندن بایت‌های خام، جدا کردن پیام‌ها با \n و تبدیل به JSON
class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(QTcpSocket *socket, QObject *parent = nullptr);
    void sendResponse(const QJsonObject &response);

signals:
    void requestReceived(const QJsonObject &request);
    void disconnected();

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer; // چون TCP یه جریان پیوسته‌ست، ممکنه یه پیام توی چند تیکه برسه
};

#endif // CLIENTHANDLER_H

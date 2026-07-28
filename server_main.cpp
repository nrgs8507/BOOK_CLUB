#include <QCoreApplication>
#include <QDebug>
#include <memory>
#include "src/models/User.h"
#include "src/repository/filerepository.h"
#include "src/auth/AuthManager.h"
#include "src/network/tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    auto userRepo = std::make_shared<FileRepository<User>>("data/users.json");
    auto authManager = std::make_shared<AuthManager>(userRepo);

    TcpServer server(authManager);
    quint16 port = 5050;

    if (!server.listen(QHostAddress::Any, port)) {
        qCritical() << "Server failed to start:" << server.errorString();
        return 1;
    }

    qInfo() << "Server is listening on port" << port;
    return app.exec();
}
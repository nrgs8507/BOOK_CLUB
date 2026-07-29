#include "tcpserver.h"
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QJsonArray>

TcpServer::TcpServer(std::shared_ptr<AuthManager> authManager,BookManager* bookManager, QObject *parent)
    : QTcpServer(parent), authManager(authManager) , bookManager(bookManager){}

QJsonObject TcpServer::bookToJson(const Book& book)
{
    QJsonObject obj;
    obj["bookId"] = book.getBookId();
    obj["title"] = book.getTitle();
    obj["author"] = book.getAuthor();
    obj["genre"] = book.getGenre();
    obj["price"] = book.getPrice();
    obj["finalPrice"] = book.getFinalPrice();
    obj["averageRating"] = book.hasReviews() ? book.getAverageRating() : -1.0;

    QByteArray imageBytes;
    QString imagePath = book.getCoverImagePath();
    if (!imagePath.isEmpty()) {
        QFile imgFile(imagePath);
        if (imgFile.open(QIODevice::ReadOnly)) {
            imageBytes = imgFile.readAll();
        }
    }
    obj["coverImageBase64"] = QString::fromLatin1(imageBytes.toBase64());

    return obj;
}

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
    else if (action == "getSecurityQuestion") {
        QString username = request.value("username").toString();
        auto user = authManager->findUser(username);
        if (user) {
            response["status"] = "ok";
            response["securityQuestion"] = user->getSecurityQuestion();
        } else {
            response["status"] = "error";
            response["message"] = "Username not found.";
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
    else if (action == "getAllBooks") {
        QJsonArray booksArray;
        for (const Book& b : bookManager->getActiveBooks()) {
            booksArray.append(bookToJson(b));
        }
        response["status"] = "ok";
        response["books"] = booksArray;
    }
    else if (action == "searchBooks") {
        QString searchBy = request.value("searchBy").toString();
        QString query = request.value("query").toString();

        QVector<Book> results;
        if (searchBy == "title") results = bookManager->searchByTitle(query);
        else if (searchBy == "author") results = bookManager->searchByAuthor(query);
        else if (searchBy == "genre") results = bookManager->searchByGenre(query);

        QJsonArray booksArray;
        for (const Book& b : results) {
            if (b.getIsActive()) booksArray.append(bookToJson(b));
        }
        response["status"] = "ok";
        response["books"] = booksArray;
    }
    else {
        response["status"] = "error";
        response["message"] = "Unknown action: " + action;
    }

    client->sendResponse(response);
}

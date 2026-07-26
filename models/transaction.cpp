#include "transaction.h"

Transaction::Transaction() : transactionId(-1), userId(-1), bookId(-1), price(0.0),
    date(QDate::currentDate()) {}

Transaction::Transaction(int transactionId, int userId, int bookId, double price,
                         const QDate& date)
    : transactionId(transactionId), userId(userId), bookId(bookId), price(price), date(date) {}

int Transaction::getId() const { return transactionId; }
int Transaction::getTransactionId() const { return transactionId; }
int Transaction::getUserId() const { return userId; }
int Transaction::getBookId() const { return bookId; }
double Transaction::getPrice() const { return price; }
QDate Transaction::getDate() const { return date; }

QJsonObject Transaction::toJson() const {
    QJsonObject obj;
    obj["transactionId"] = transactionId;
    obj["userId"] = userId;
    obj["bookId"] = bookId;
    obj["price"] = price;
    obj["date"] = date.toString(Qt::ISODate);
    return obj;
}

Transaction Transaction::fromJson(const QJsonObject& obj) {
    return Transaction(
        obj["transactionId"].toInt(),
        obj["userId"].toInt(),
        obj["bookId"].toInt(),
        obj["price"].toDouble(),
        QDate::fromString(obj["date"].toString(), Qt::ISODate)
        );
}
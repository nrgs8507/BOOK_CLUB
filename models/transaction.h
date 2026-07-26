#pragma once
#include <QDate>
#include <QJsonObject>

class Transaction {
private:
    int transactionId;
    int userId;
    int bookId;
    double price;
    QDate date;

public:
    Transaction();
    Transaction(int transactionId, int userId, int bookId, double price,
                const QDate& date = QDate::currentDate());

    int getId() const;
    int getTransactionId() const;
    int getUserId() const;
    int getBookId() const;
    double getPrice() const;
    QDate getDate() const;

    QJsonObject toJson() const;
    static Transaction fromJson(const QJsonObject& obj);
};
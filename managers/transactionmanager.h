#pragma once
#include "../repositories/itransactionstorage.h"
#include <QVector>

class TransactionManager {
private:
    ITransactionStorage* storage;

    int generateNewId() const;

public:
    explicit TransactionManager(ITransactionStorage* storage);

    int recordTransaction(int userId, int bookId, double price);

    QVector<Transaction> getTransactionsByUser(int userId);
    QVector<Transaction> getTransactionsByBook(int bookId);


    double getTotalRevenueForBook(int bookId);
};
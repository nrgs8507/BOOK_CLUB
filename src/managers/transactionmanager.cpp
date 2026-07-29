#include "transactionmanager.h"
#include <algorithm>

TransactionManager::TransactionManager(ITransactionStorage* storage) : storage(storage) {}

int TransactionManager::generateNewId() const {
    QVector<Transaction> all = storage->getAll();
    int maxId = 0;
    for (const Transaction& t : all) {
        maxId = std::max(maxId, t.getId());
    }
    return maxId + 1;
}

int TransactionManager::recordTransaction(int userId, int bookId, double price) {
    int newId = generateNewId();
    Transaction newTransaction(newId, userId, bookId, price);
    storage->save(newTransaction);
    return newId;
}

QVector<Transaction> TransactionManager::getTransactionsByUser(int userId) {
    return storage->getByUserId(userId);
}

QVector<Transaction> TransactionManager::getTransactionsByBook(int bookId) {
    return storage->getByBookId(bookId);
}

double TransactionManager::getTotalRevenueForBook(int bookId) {
    double total = 0.0;
    for (const Transaction& t : storage->getByBookId(bookId)) {
        total += t.getPrice();
    }
    return total;
}
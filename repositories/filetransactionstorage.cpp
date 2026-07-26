#include "filetransactionstorage.h"

FileTransactionStorage::FileTransactionStorage(const QString& path)
    : FileRepository<Transaction>(path) {}

QVector<Transaction> FileTransactionStorage::getByUserId(int userId) {
    QVector<Transaction> result;
    for (const Transaction& t : getAll()) {
        if (t.getUserId() == userId) {
            result.append(t);
        }
    }
    return result;
}

QVector<Transaction> FileTransactionStorage::getByBookId(int bookId) {
    QVector<Transaction> result;
    for (const Transaction& t : getAll()) {
        if (t.getBookId() == bookId) {
            result.append(t);
        }
    }
    return result;
}
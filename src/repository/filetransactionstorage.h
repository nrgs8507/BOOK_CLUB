#pragma once
#include "filerepository.h"
#include "itransactionstorage.h"
#include "../models/transaction.h"

class FileTransactionStorage : public FileRepository<Transaction>, public ITransactionStorage {
public:
    explicit FileTransactionStorage(const QString& path);

    QVector<Transaction> getByUserId(int userId) override;
    QVector<Transaction> getByBookId(int bookId) override;
};
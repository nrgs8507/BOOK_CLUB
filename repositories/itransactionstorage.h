#pragma once
#include "irepository.h"
#include "../models/transaction.h"
#include <QVector>

class ITransactionStorage : public virtual IRepository<Transaction> {
public:
    virtual ~ITransactionStorage() = default;

    virtual QVector<Transaction> getByUserId(int userId) = 0;
    virtual QVector<Transaction> getByBookId(int bookId) = 0;
};